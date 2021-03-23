import * as express from "express";
import axios, { AxiosRequestConfig } from "axios";
import * as coo from "cookie-parser";

const app = express();
const port = 4000;
app.use(coo())

const tokens = {};

const getconfig = (
  code: string,
  secret: string,
  client: string
): AxiosRequestConfig => {
  var config: AxiosRequestConfig = {
    method: "post",
    url: `https://github.com/login/oauth/access_token`,
    data: {
      code: code,
      client_id: client,
      client_secret: secret,
    },
  };
  return config;
};

//vogue first makes the get request to this endpoint and the purpose of this endpoint is to 
//remove one param called "redirect_uri" which is added by next-auth, the request is then redirected to github.
app.get("/auth", (req, res) => {
  //console.log(req.query)
  let { client_id, state, scope } = req.query; // state needs to carry comma separated url and a unique code, possibly hashed 
  //console.log(state);
  const pair = state.split(",");
  tokens[state] = { code: "", client: client_id, url: pair[0] }; // adds the client_id and url to a global object with the uid being key
  console.log(JSON.stringify(req.cookies))
  //res.redirect(
    //`https://github.com/login/oauth/authorize?state=${state}&scope=${scope}&client_id=${client_id}`
  //);
  res.redirect(
    `https://github.com/login/oauth/authorize?state=${state}&client_id=${client_id}`
  );
});

//this is the endpoint where github is supposed to redirect on clicking authorize
//I was unable to get the code and client secret when next-auth makes the request for acquiring the token
//So, I save the code in the object for this app.
app.get("/callback", (req, res) => {
  const { code, state } = req.query;
  console.log(JSON.stringify(req.cookies))
  tokens[state] = { ...tokens[state], code: code };
  //console.log(code);
  res.redirect(
  `http://localhost:3000/api/auth/callback/github?code=${code}&state=${state}` // has to be replaced by the url we will save in the object
  );
});

//The /token endpoint will return the token from github after making a post request and then next-auth will create the session.
//This way we can have deployment previews working for github specific oauth flow.
app.post("/token", (req, res) => {
  //console.log(req.query);
  const { state, secret } = req.query;
  //console.log(tokens[state])
  console.log(req.cookies)

  axios(getconfig(tokens[state].code, secret, tokens[state].client))
  .then(function (response) {
    let url = new URL("https://example.com?" + response.data);
    let params = new URLSearchParams(url.search);
    res.json({
      access_token: params.get("access_token"),
      token_type: params.get("token_type"),
    });
  })
  .catch(function (error) {
    console.log(error);
    res.json({});
  });

  delete tokens[state];
});


app.listen(port, () => {
  console.log(`Assignment app listening at http://localhost:${port}`);
});
