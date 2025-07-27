#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Data structure to hold interactive data visualization elements
struct VisualizationElement {
    string type; // e.g. bar chart, scatter plot, etc.
    string label;
    vector<double> data;
    map<string, string> options; // e.g. color, size, etc.
};

// Interactive data visualization parser class
class DataVisualizationParser {
public:
    vector<VisualizationElement> parse(string input) {
        vector<VisualizationElement> elements;

        // Tokenize input string
        vector<string> tokens = tokenize(input);

        // Parse tokens and create visualization elements
        for (string token : tokens) {
            VisualizationElement element;
            size_t pos = token.find(":");
            if (pos != string::npos) {
                element.type = token.substr(0, pos);
                string params = token.substr(pos + 1);
                size_t labelPos = params.find(",");
                if (labelPos != string::npos) {
                    element.label = params.substr(0, labelPos);
                    string dataStr = params.substr(labelPos + 1);
                    parseData(dataStr, element.data);
                }
            }
            elements.push_back(element);
        }

        return elements;
    }

private:
    vector<string> tokenize(string input) {
        vector<string> tokens;
        size_t pos = 0;
        while ((pos = input.find(";")) != string::npos) {
            tokens.push_back(input.substr(0, pos));
            input.erase(0, pos + 1);
        }
        tokens.push_back(input);
        return tokens;
    }

    void parseData(string input, vector<double>& data) {
        size_t pos = 0;
        while ((pos = input.find(",")) != string::npos) {
            data.push_back(stod(input.substr(0, pos)));
            input.erase(0, pos + 1);
        }
        data.push_back(stod(input));
    }
};

int main() {
    DataVisualizationParser parser;
    string input = "bar_chart:Sales,10.5,20.2,30.1,40.5,50.8;scatter_plot:Temperature,23.2,12.1,34.5,56.7,11.2";
    vector<VisualizationElement> elements = parser.parse(input);

    for (VisualizationElement element : elements) {
        cout << "Type: " << element.type << ", Label: " << element.label << endl;
        cout << "Data: ";
        for (double value : element.data) {
            cout << value << " ";
        }
        cout << endl << endl;
    }

    return 0;
}