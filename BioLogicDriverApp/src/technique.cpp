#include "technique.h"

#include <map>

Technique::Technique(string name): name(name) {
    
}

Technique::~Technique() {

}

TEccParams_t Technique::getEccParams() {
    TEccParams_t r{};
    vector<TEccParam_t> params;
    for(auto const& x : singles) {
        TEccParam_t p;
        BL_DefineSglParameter(const_cast<char*>(x.first.c_str()), (float) x.second, 0, &p);
        params.push_back(p);
    }
    for(auto const& x : ints) {
        TEccParam_t p;
        BL_DefineIntParameter(const_cast<char*>(x.first.c_str()), x.second, 0, &p);
        params.push_back(p);
    }
    for(auto const& x : bools) {
        TEccParam_t p;
        BL_DefineBoolParameter(const_cast<char*>(x.first.c_str()), x.second, 0, &p);
        params.push_back(p);
    }
    //array funnies
    for(auto const& x : singleArrays) {
        for(size_t i = 0; i < x.second.size(); i++) {
            TEccParam_t p;
            BL_DefineSglParameter(const_cast<char*>(x.first.c_str()), (float) x.second[i], i, &p);
            params.push_back(p);
        }
    }
    for(auto const& x : intArrays) {
        for(size_t i = 0; i < x.second.size(); i++) {
            TEccParam_t p;
            BL_DefineIntParameter(const_cast<char*>(x.first.c_str()), x.second[i], i, &p);
            params.push_back(p);
        }
    }
    for(auto const& x : boolArrays) {
        for(size_t i = 0; i < x.second.size(); i++) {
            TEccParam_t p;
            BL_DefineBoolParameter(const_cast<char*>(x.first.c_str()), x.second[i], i, &p);
            params.push_back(p);
        }
    }
    r.len = params.size();
    r.pParams = params.data();

    return r;
}

void Technique::addParam(string name, double value) {
    singles[name] = value;
}

void Technique::addParam(string name, int value) {
    ints[name] = value;
}

void Technique::addParam(string name, bool value) {
    bools[name] = value;
}

void Technique::addParamArray(string name, vector<double> value) {
    singleArrays[name] = value;
}

void Technique::addParamArray(string name, vector<int> value) {
    intArrays[name] = value;
}

void Technique::addParamArray(string name, vector<bool> value) {
    boolArrays[name] = value;
}

void Technique::addParamArrayValue(string name, double value) {
    singleArrays[name].push_back(value);
}

void Technique::addParamArrayValue(string name, int value) {
    intArrays[name].push_back(value);
}

void Technique::addParamArrayValue(string name, bool value) {
    boolArrays[name].push_back(value);
}