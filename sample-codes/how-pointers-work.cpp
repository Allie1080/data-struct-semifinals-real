#include <iostream> 
#include <string>
#include <vector>

struct PointlessMap {
    std::vector<std::string> landmarks;
    int size;

};

struct Map {
    std::vector<std::string> *landmarks;
    int size;

};

int incrementNumber (int number) {
   return number++;
   
}

int incrementNumber (int *number) {
    return *number++;

}

int main () {


}