/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileIOLib.h
 *
 * Created on July 1, 2021, 8:05 AM
 */

#ifndef UTIL_FILEIOLIB_H_
#define UTIL_FILEIOLIB_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>

class DataFrame{
private:
    std::unordered_map<std::string, std::vector<std::string> > map;
    std::vector<std::string> columns;
    int m_nrows;
  
public:
    DataFrame(){
        m_nrows = 0;
    }
    DataFrame(std::string filename, char delimiter=','){
        m_nrows = 0;
        read(filename, delimiter);
    }
    DataFrame(const DataFrame& frame){
        for(auto it=frame.map.begin(); it != frame.map.end(); it++){
            this->map.insert({it->first, it->second});
        }
        this->columns = frame.columns;
        this->m_nrows = frame.m_nrows;
    }
    DataFrame& operator=(const DataFrame& frame){
        for(auto it=frame.map.begin(); it != frame.map.end(); it++){
            this->map.insert({it->first, it->second});
        }
        this->columns = frame.columns;
        this->m_nrows = frame.m_nrows;
        return *this;
    }
    
    ~DataFrame(){}
    
    int nrows(){
        return m_nrows;
    }
    int ncols(){
        return map.size();
    }
    
    void add(std::string col_name, std::vector<std::string>& col_data){
        columns.push_back(col_name);
        m_nrows = max(m_nrows, (int)col_data.size());
        this->map.insert({col_name, std::vector<std::string>(col_data)});
    }
    //
    std::vector<std::string>& operator[](std::string col_name){
        return this->map[col_name];
    }
    std::vector<std::string> get_columns(){
        return this->columns;
    }
    void read(std::string filename, char delimiter=','){
        //open stream
        ifstream datastream(filename);
        if(!datastream.is_open()){
            cerr << filename << ": couldn't open for reading" << std::endl;
        }
        //read header
        read_header(datastream, delimiter);
                
        //read lines
        std::string line;
        while(getline(datastream, line)){
            //parse line
            istringstream linestream(line);
            std::string item;
            int col_idx = 0;
            while(getline(linestream, item, delimiter)){
                std::string col_name = columns[col_idx];
                this->map[col_name].push_back(item);
                col_idx += 1;
            }
        }
        
        //close stream
        datastream.close();
    }
    void write(std::string filename, char delimiter=','){
        //open stream
        ofstream datastream(filename);
        if(!datastream.is_open()){
            cerr << filename << ": couldn't open for writing" << std::endl;
        }
        //write header
        write_header(datastream, delimiter);
        
        //write lines
        int _nrows = nrows();
        int _ncols = ncols();
        for(int rowIdx=0; rowIdx < _nrows; rowIdx++){
            for(int colIdx=0; colIdx < _ncols - 1; colIdx++){
                std::string col_name = columns[colIdx];
                if(rowIdx > this->map[col_name].size() - 1)
                    datastream << "None" << delimiter << " ";
                else
                    datastream << this->map[col_name][rowIdx] << delimiter << " ";
            }
            if(_ncols > 0){
                std::string col_name = columns[_ncols - 1];
                if(rowIdx > this->map[col_name].size() - 1)
                    datastream << "None" << std::endl;
                else
                    datastream << this->map[col_name][rowIdx] << std::endl;
            }
        }
        
        //close stream
        datastream.close();
    }
    
private:
    void read_header(ifstream& datastream, char delimiter=','){
        std::string line;
        if(getline(datastream, line)){
            //parse line
            istringstream linestream(line);
            std::string col;
            while(getline(linestream, col, delimiter)){
                this->columns.push_back(col);
                this->map[col] = std::vector<std::string>();
            }
        }
    }
    void write_header(ofstream& datastream, char delimiter=','){
        for(int cidx=0; cidx < this->columns.size() - 1; cidx++)
            datastream << this->columns[cidx] << delimiter;
        if(this->columns.size() > 0)
            datastream << this->columns[this->columns.size() - 1] << std::endl;
    }
};

#endif /* FILEIOLIB_H */

