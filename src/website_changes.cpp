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

  std::vector<std::string> output_website_directions;
  rapidcsv::Document doc("src/lab_tracking.csv");
  std::vector<std::string> current_person_col = doc.GetColumn<std::string>("current_person");
  std::vector<std::string> website_person_col = doc.GetColumn<std::string>("website_person");
  std::vector<std::string> current_title_col = doc.GetColumn<std::string>("current_title");
  std::vector<std::string> website_title_col = doc.GetColumn<std::string>("website_title");

  std::vector<int> website_index_to_ignore;

  
  for (int i= 0 ; i< current_person_col.size(); i++) {
    bool name_matched = false;
    const std::string current_person_val = current_person_col[i];
    const std::string current_title_val = current_title_col[i];

    for (int j = 0; j < website_person_col.size(); j++) {
      const std::string website_person_val = website_person_col[j];
      const std::string website_title_val = website_title_col[j];

      if (current_person_val == website_person_val) {

        name_matched = true;

        // check for position match:

        if (current_title_val == website_title_val) {
        } else {
          // if the titles do not match, we need to perform an operation here:
          // Need to MOVE current_person_val FROM 
          std::string output("MOVE," + current_person_val + "," + "Current Members" +","+ website_title_val + "," + "Current_Members" + "," + current_title_val);
          output_website_directions.push_back(output);

        }

        website_index_to_ignore.push_back(j);

      } 
      continue;
    }

    if (!name_matched) {
      std::string output("ADD," + current_person_val + "," + " " + "," + " " + "," + "Current Members" +"," + current_title_val);
      output_website_directions.push_back(output);
    }

  }


  std::sort(website_index_to_ignore.begin(), website_index_to_ignore.end());
  //for(auto index: website_index_to_ignore) {
  //  std::cout << index << std::endl;
  //}
  std::cout << std::endl;
  std::cout << "Place this text into your excel sheet to see changes that need to be made to website:" << std::endl;
  for (int k = 0; k < website_person_col.size(); k++) {
    auto website_person_val = website_person_col[k];
    if(std::count(website_index_to_ignore.begin(), website_index_to_ignore.end(), k) || website_person_col[k].empty()) {
      continue;
    }
    //this list of people are the ones that are on the website already and are no longer a part of the lab
    std::string output("MOVE,"+website_person_val+","+"Current Members" +","+ website_title_col[k] +","+"Alumni"+","+website_title_col[k]);
    output_website_directions.push_back(output);
  }

  for(auto value: output_website_directions) {
    std::cout << value << std::endl;
  }



  return 0;
}
