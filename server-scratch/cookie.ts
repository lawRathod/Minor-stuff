import * as express from "express";
import * as cookiesParser from 'cookie-parser';

const app = express();
const port = 4000;

app.use(cookiesParser())

app.get("/", (req, res) => {
  let options = {
    maxAge: 1000 * 60 * 15, // would expire after 15 minutes
    httpOnly: true, // The cookie only accessible by the web server
    //signed: true // Indicates if the cookie should be signed
  }
  res.cookie('secret', 'hihahahhahah', options)
  res.send('cookie set')
})

app.get("/try", (req, res) =>{
  console.log(req.cookies)
  res.send('cookies read')
})

app.listen(port, () => {
  console.log(`Assignment app listening at http://localhost:${port}`);
});
