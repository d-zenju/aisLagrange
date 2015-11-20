//
//  main.cpp
//  aivdm
//
//  Created by ZENJU Daisuke on 2015/10/20.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>


struct aivdm_type1 {
    int time;
    int messageType;
    int repeatIndicator;
    int mmsi;
    std::string navigationStatus;
    std::string rot;
    double sog;
    std::string positionAccuracy;
    double longitude;
    double latitude;
    double cog;
    int hdg;
    int timeStamp;
    std::string maneuverIndicator;
    std::string spare;
    std::string raimFlag;
    int radioStatus;
};


// AIVDM(Type1)のデータを読み込む, string型にsetする
aivdm_type1 readAivdmType1(std::string str) {
    aivdm_type1 nmea;
    
    int i = 0;
    std::string tmp[17];
    std::istringstream stream(str);
    while(getline(stream,tmp[i],','))
        ++i;
    
    nmea.time = std::atoi(tmp[0].c_str());
    nmea.messageType = std::atoi(tmp[1].c_str());
    nmea.repeatIndicator = std::atoi(tmp[2].c_str());
    nmea.mmsi = std::atoi(tmp[3].c_str());
    nmea.navigationStatus = tmp[4];
    nmea.rot = tmp[5];
    nmea.sog = std::atof(tmp[6].c_str());
    nmea.positionAccuracy = tmp[7];
    nmea.longitude = std::atof(tmp[8].c_str());
    nmea.latitude = std::atof(tmp[9].c_str());
    nmea.cog = std::atof(tmp[10].c_str());
    nmea.hdg = std::atoi(tmp[11].c_str());
    nmea.timeStamp = std::atoi(tmp[12].c_str());
    nmea.maneuverIndicator = tmp[13];
    nmea.spare = tmp[14];
    nmea.raimFlag = tmp[15];
    nmea.radioStatus = std::atoi(tmp[16].c_str());
    
    return nmea;
}



int main(int argc, const char * argv[]) {
    
    aivdm_type1 aivdm;
    std::multimap<int, aivdm_type1> data;
    std::map<int, aivdm_type1> now;
    
    // ファイル読み込み(AIVDM(Type1))
    std::ifstream ifs("/Users/zenju/Documents/XcodeProject/aivdm/dec1.csv");
    if (ifs.fail()) {
        std::cerr << "Error : Can't open this file." << std::endl;
        return -1;
    }
    
    std::string str;
    while (getline(ifs, str)) {
        aivdm = readAivdmType1(str);
        data.insert(std::make_pair(aivdm.time, aivdm));
    }
    ifs.close();
    
    /*
    auto itr = data.find(234226);
    if (itr != data.end()) {
        std::cout << itr->first << " " << itr->second.mmsi << std::endl;
    }
    
    auto mtr = data.upper_bound(234226);
    if (mtr != data.end()) {
        std::cout << mtr->first << " " << mtr->second.mmsi << std::endl;
    }
    
    while (itr != mtr) {
        std::cout << itr->first << " " << itr->second.mmsi << std::endl;
        ++itr;
    }*/
    
    
    auto itr = data.upper_bound(234426);
    
    for (auto btr = data.begin(); btr != itr; ++btr) {
        aivdm = btr->second;
        int mmsi = aivdm.mmsi;
        now[mmsi] = aivdm;
    }
    
    for (auto btr = now.begin(); btr != now.end(); ++btr) {
        std::cout << btr->first << " " << btr->second.time << std::endl;
    }
    
    
    return 0;
}