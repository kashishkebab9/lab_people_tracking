#include <iostream>
#include <vector>
#include <string>
#include "../include/rapidcsv.h"

//things to check for in the csv TODO:
// whether there is a single instance for every Person
// if the column sizes make sense throughout the csv

int main() {
  std::cout << "This is a script to automate the people tracking in KumarLab" << std::endl;

  std::vector<std::string> output_website_directions;
  rapidcsv::Document doc("src/lab_tracking.csv");
  std::vector<std::string> current_person_col = doc.GetColumn<std::string>("current_person");
  std::vector<std::string> website_person_col = doc.GetColumn<std::string>("website_person");
  std::vector<std::string> current_title_col = doc.GetColumn<std::string>("current_title");
  std::vector<std::string> website_title_col = doc.GetColumn<std::string>("website_title");

  
  for (int i= 0 ; i< current_person_col.size(); i++) {
    bool name_matched = false;
    std::cout << "Current Person: " << current_person_col[i] << std::endl;
    std::string current_person_val = current_person_col[i];
    std::string current_title_val = current_title_col[i];

    for (int j = 0; j < website_person_col.size(); j++) {
      std::cout << "Website Member: " << website_person_col[j] << std::endl; 
      std::string website_person_val = website_person_col[j];
      std::string website_title_val = website_title_col[j];

      if (current_person_val == website_person_val) {
        //want to remove member from both vectors:
        website_person_col.erase(website_person_col.begin()+j);
        current_person_col.erase(current_person_col.begin()+i);
        std::cout << "We got a name match!" <<std::endl; 
        name_matched = true;

        // check for position match:
        std::cout << "Current Title: " << current_title_val << std::endl;
        std::cout << "Website Title: " << website_title_val << std::endl;

        if (current_title_val == website_title_val) {
          std::cout << "Do not move this individual from the current members of the lab on the website" << std::endl;
        } else {
          // if the titles do not match, we need to perform an operation here:
          // Need to MOVE current_person_val FROM 
          std::string output("MOVE," + current_person_val + "," + "Current_Members" +","+ website_title_val + "," + "Current_Members" + "," + current_title_val);
          output_website_directions.push_back(output);

        }

      } 
      continue;
    }

    if (!name_matched) {
      std::cout << "Did not find this name in the website!" << std::endl;
      std::string output("ADD," + current_person_val + "," + " " + "," + " " + "," + "current_members" +"," + current_title_val);
      output_website_directions.push_back(output);
    }

  }

  for(auto value: output_website_directions) {
    std::cout << value << std::endl;
  }




  return 0;
}
