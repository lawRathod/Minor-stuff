#include"parse.h"
#include<iostream>
#include<regex>

namespace Utils {

	raster::raster(std::string hdrfile, std::string datfile){
		this->hdrfile = hdrfile;
		this->datfile = datfile;
		read_metadata();
	}

	void raster::read_metadata(){

		std::ifstream header;
		header.open(hdrfile);
		std::string line;

		while(header){
			getline(header, line);
			int equal_pos = line.find("=");
			if(equal_pos > -1){
				std::string key =line.substr(0, equal_pos-1);
				key = std::regex_replace(key.c_str(), std::regex("^ +| +$|( ) +"), "$1");
				std::string value = line.substr(equal_pos + 2);
				value = std::regex_replace(value.c_str(), std::regex("^ +| +$|( ) +"), "$1");
				if((int)value.find("{") > -1){
					while((int)value.find("}") <0){
						getline(header, line);
						value.append(line);
					}
				}
				metadata.insert(std::pair<std::string, std::string>(key, value));
			}
		}

		header.close();
	}

	template<typename T>
	void* raster::read_bin_internal(){
		std::stringstream *ss;
		ss = new std::stringstream(metadata.at("bands"));
		int bands;
		*ss >> bands;
		ss = new std::stringstream(metadata.at("samples"));
		int samples;
		*ss >> samples;
		ss = new std::stringstream(metadata.at("lines"));
		int lines;
		*ss >> lines;

		p = new T [bands * lines * samples];
		std::ifstream bin(datfile, std::ios::out | std::ios::binary);

		int count = 0;
		for(int i=0;i<bands; i++){
			for(int j=0;j<samples; j++){
				for(int k=0;k<lines;k++){
					bin.read((char *) &*(static_cast<T*>(p) + i*samples*lines + j*lines + k), sizeof(static_cast<T*>(p)));
					count++;
				}
			}
		}

		bin.close();

		return p;

	}

	void* raster::read_bin(){
		if(metadata.at("data type").compare("2\r") == 0){
			return read_bin_internal<int16_t>();
		}
		if(metadata.at("data type").compare("1\r") == 0){
			return read_bin_internal<uint8_t>();
		}
		return NULL;
	}


	std::string raster::get_metadata(std::string key){
		return metadata.at(key);
	}

	std::unordered_map<std::string, std::string> raster::get_metadata_object(){
		return metadata;
	}

	template<typename T>
	void raster::print_data_sample_internal(void* data, int band_from_hdr, int sample_num){
		std::stringstream ss(metadata.at("lines  "));
		int lines;
		ss>>lines;
		for(int i=0;i<band_from_hdr; i++){
			for(int j=0;j<sample_num; j++){
				for(int k=0;k<lines;k++){
					std::cout<<*(static_cast<T*>(data) + i*sample_num*lines + j*lines + k)<<" ";
				}
				std::cout<<std::endl;
			}
			std::cout<<std::endl;
		}
	}
	void raster::print_data_sample(void* data, int band_from_hdr, int sample_num){
		if(metadata.at("data type") == "2\r"){
			print_data_sample_internal<int16_t>(data, band_from_hdr, sample_num);
		}else if (metadata.at("data type") == "1\r"){
			print_data_sample_internal<uint8_t>(data, band_from_hdr, sample_num);
		}
	}

}



//int main() {
	//Utils::raster* obj = new Utils::raster("CupriteAVIRISSubset.hdr", "CupriteAVIRISSubset.dat");
	//std::unordered_map<std::string, std::string> meta = obj->get_metadata_object();

	////for(auto i = meta.begin(); i != meta.end(); i++){
		////std::cout<<i->first<<" : "<< i->second<<std::endl;
	////}
	
	//std::cout<<meta.at("wavelength")<<std::endl;
	
	



	//return 0;

//}
