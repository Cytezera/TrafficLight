#include <vector>

#include <iostream> 
#include <chrono>
#include <thread> 
using namespace std; 

struct TrafficLightColour{
	string colour; 
	int timer; 
};
int globalTimer = 1; 
class TrafficLight{ 
public: 
	TrafficLightColour red = {"RED",5};
	TrafficLightColour green = {"GREEN", 3}; 
	TrafficLightColour yellow = {"YELLOW", 2}; 

	TrafficLightColour* currentLight[3]; //creating a pointer in an array form to store all the structs at once  
	int currentIndex = 0 ;
	TrafficLight(): currentLight{ &red, &green, &yellow}, currentIndex(0) {} ; //Allowing it to acess each struct address through numbers 
	void displayLight(const string inter){
		cout << inter << "Light : " << currentLight[currentIndex]->colour  << endl; 
		
	}
	void waitLight(){

		this_thread::sleep_for(chrono::seconds(currentLight[currentIndex]->timer)); 
	}

	void changeLight(){
		
		currentIndex = (currentIndex + 1) % 3 ; 
	}
	void pauseLight(string inter){
		cout << inter << "Light : RED" << endl; 
		this_thread::sleep_for(chrono::seconds(2)); 
	}
	void trafficLightTimer(const string inter , int startingIndex){
		currentIndex = startingIndex;
		while(true){
			
			if (currentIndex != 0) {
				displayLight(inter); 
			}
			waitLight(); 
			if (currentIndex != 1) {

				pauseLight(inter); 
			}
			changeLight(); 
		}
	}	


};
int main (){
	TrafficLight light1; 
	TrafficLight light2; 
	vector<thread> threads; 
	
       	threads.emplace_back(&TrafficLight::trafficLightTimer, &light1 , "Intersection 1 ", 0  ) ; 
	threads.emplace_back(&TrafficLight::trafficLightTimer, &light2, "Intersection 2" , 1 ) ; 	
	for (auto& thread: threads){
		thread.join();
	}
	return 0 ;
}
