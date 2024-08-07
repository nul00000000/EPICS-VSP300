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
    r.pParams = new TEccParam_t[r.len];

    for(int i = 0; i < params.size(); i++) {
        r.pParams[i] = params[i];
    }

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

double Technique::getSingle(string param) {
    if(!singles.count(param)) {
        return 0;
    }
    return singles[param];
}

int Technique::getInt(string param) {
    if(!ints.count(param)) {
        return 0;
    }
    return ints[param];
}

bool Technique::getBool(string param) {
    if(!bools.count(param)) {
        return 0;
    }
    return bools[param];
}

vector<double> Technique::getSingles(string param) {
    if(!singleArrays.count(param)) {
        return vector<double>();
    }
    return singleArrays[param];
}

vector<int> Technique::getInts(string param) {
    if(!intArrays.count(param)) {
        return vector<int>();
    }
    return intArrays[param];
}

vector<bool> Technique::getBools(string param) {
    if(!boolArrays.count(param)) {
        return vector<bool>();
    }
    return boolArrays[param];
}