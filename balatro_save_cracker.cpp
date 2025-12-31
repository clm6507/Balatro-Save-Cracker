#include "./utils.hpp"
#include "items.hpp"
#include <map>
#include <iomanip>
#include <string>
#include <random>
#include <ctime>

#define ALPHANUMERIC_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

const char ALPHANUMERIC_ARRAY[] = ALPHANUMERIC_CHARS;
const int ALPHANUMERIC_SIZE = 36;

LuaRandom rng;
std::string seed;
double hashedSeed;
std::map<std::string, double> nodes;
std::string anteStr = std::to_string(1);

double get_node(std::string ID) {
    if (nodes.count(ID) == 0) {
        nodes[ID] = pseudohash(ID+seed);
    }
    nodes[ID] = round13(std::fmod(nodes[ID]*1.72431234+2.134453429141,1));
    return (nodes[ID] + hashedSeed)/2;
}

double random(std::string ID) {
    rng = LuaRandom(get_node(ID));
    return rng.random();
}

std::string get_new_seed(){
    std::string new_seed = "";
    for(int i = 0; i < 8; i++){
        new_seed = new_seed + ALPHANUMERIC_ARRAY[rand() % ALPHANUMERIC_SIZE];
    }
    
    return new_seed;
}

int randint(std::string ID, int min, int max) {
    rng = LuaRandom(get_node(ID));
    return rng.randint(min, max);
}


std::string randchoice(std::string ID, std::vector<std::string> items) {
    rng = LuaRandom(get_node(ID));
    std::string item = items[rng.randint(0, items.size()-1)];
    return item;
}

int main(int argc, char* argv[]){
    srand(static_cast<unsigned int>(time(NULL)));
    /*
    for(int i = 0; i < 100000; i++){
        seed = get_new_seed();
        hashedSeed = pseudohash(seed);
        nodes.clear();
        rng = LuaRandom(0);
        rng = LuaRandom(get_node("Joker4"));
	    int legendary_joker = rng.randint(0,4);
	    if(legendary_joker == 4){
		    rng = LuaRandom(get_node("Joker4"));
            double negative_poll = random("edisou1");
            if(negative_poll > 0.997){
                for(int j = 0; j < 6; j++){
                    double soul_poll = random("soul_Tarot1");
                    if(soul_poll > 0.997){
                        std::cout << seed << std::endl;
                        break;
                    }
                }
            }
	    }
    }
    */
    rng = LuaRandom(0);
    seed = "VE5F7QW3";
    hashedSeed = pseudohash(seed);
    
    std::cout << randchoice("Joker4", LEGENDARY_JOKERS) << std::endl;
    
    nodes.clear();
    rng = LuaRandom(0);
    seed = "11111111";
    hashedSeed = pseudohash(seed);
    std::cout << randchoice("Joker1sho1", COMMON_JOKERS) << std::endl;


    nodes.clear();
    rng = LuaRandom(0);
    seed = "8P7W6QG5";
}