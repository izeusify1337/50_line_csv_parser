#include <string>
#include <vector>
#include <fstream>
#include <map>

std::map<std::string, std::vector<std::string>> parse(const std::string &path) {
	std::map<std::string, std::vector<std::string>> parsed; // it is returned
	std::vector<std::string> columns; // this needs to exist because std::map doesnt store stuff in the order it was created.
	std::string line, current_column; 
	bool columns_parsed = false;
	std::ifstream csv_file(path);

	while (std::getline(csv_file, line))
	{
		if (!columns_parsed) { // haven't parsed the column names yet.
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ',') { // current column has finished
					parsed[current_column] = std::vector<std::string>{};
					columns.push_back(current_column);
					current_column.clear();
					if (line[i + 1] == ' ')
						i++;
				}
				else if (i == line.size() - 1) { // we just finished parsing the last column
					current_column.push_back(line[i]);
					parsed[current_column] = std::vector<std::string>{};
					columns.push_back(current_column);
				}
				else { // push the column name char by char
					current_column.push_back(line[i]);
				}
			}
			columns_parsed = true;
		} // finished parsing columns
		else { // parsing cell data
			int last_entry_end = 0; 
			for (auto column : columns) { // iterating throught the column names
				std::string cur_entry;
				for (int i = last_entry_end; i < line.size(); i++) {
					if (line[i] == ',') { // current cell has finished!
						parsed[column].push_back(cur_entry);
						cur_entry.clear();
						last_entry_end = i + 1; // where the next cell starts
						if (line[i + 1] == ' ')
							last_entry_end++;
						break;
					}
					else if (i == line.size() - 1) { // last cell
						cur_entry.push_back(line[i]);
						parsed[column].push_back(cur_entry);
					}
					else {
						cur_entry.push_back(line[i]);
					}
				}
			}
		}
	}
	
	return parsed;
}