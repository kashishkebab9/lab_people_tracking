#include <iostream>
#include <vector>
#include <string>
#include "../include/rapidcsv.h"
#include <bits/stdc++.h>

//things to check for in the csv TODO:
// whether there is a single instance for every Person
// if the column sizes make sense throughout the csv

int main() {
  std::cout << "This is a script to automate the people tracking in KumarLab" << std::endl;
  std::cout << "There are some assumptions that get made in this script:" << std::endl;
  std::cout << "1. You are providing a csv with two sets of paired columns, one of the entire, current roster of KumarLab" <<std::endl;
  std::cout << "and one of the current members of the lab that are on KumarRobotics.org, and their respective positions" << std::endl;
  std::cout << "2. All names are typed exactly the same for matching members (to be fixed in the future)" << std::endl;
  std::cout << "3. The sizes of the member's names and titles columns are the same (to be fixed in the future)" <<std::endl;

  std::vector<std::string> output_drive_directions;
  rapidcsv::Document doc("src/lab_tracking.csv");
  std::vector<std::string> current_person_col = doc.GetColumn<std::string>("current_person");
  std::vector<std::string> drive_person_col = doc.GetColumn<std::string>("drive_person");

  std::vector<int> drive_index_to_ignore;

  for (int i= 0 ; i< current_person_col.size(); i++) {
    bool name_matched = false;
    const std::string current_person_val = current_person_col[i];

    for (int j = 0; j < drive_person_col.size(); j++) {
      const std::string drive_person_val = drive_person_col[j];

      if (current_person_val == drive_person_val) {
        name_matched = true;
        drive_index_to_ignore.push_back(j);
        continue;
      } 
    }

    if (!name_matched) {
      std::string output("ADD," + current_person_val);
      output_drive_directions.push_back(output);
    }

  }


  std::sort(drive_index_to_ignore.begin(), drive_index_to_ignore.end());
  //for(auto index: website_index_to_ignore) {
  //  std::cout << index << std::endl;
  //}
  std::cout << std::endl;
  std::cout << "Place this text into your excel sheet to see changes that need to be made to website:" << std::endl;
  for (int k = 0; k < drive_person_col.size(); k++) {
    if(std::count(drive_index_to_ignore.begin(), drive_index_to_ignore.end(), k) || drive_person_col[k].empty()) {
      continue;
    }
    //this list of people are the ones that are on the website already and are no longer a part of the lab
    std::string output("REMOVE,"+drive_person_col[k]);
    output_drive_directions.push_back(output);
  }

  for(auto value: output_drive_directions) {
    std::cout << value << std::endl;
  }






  return 0;
}
