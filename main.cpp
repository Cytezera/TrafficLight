#include <iostream> 
#include <chrono>
#include <thread> 
using namespace std; 

struct TrafficLightColour{
	string colour; 
	int timer; 
};
class TrafficLight{ 
public: 
	TrafficLightColour red = {"RED",5};
	TrafficLightColour green = {"GREEN", 4}; 
	TrafficLightColour yellow = {"YELLOW", 2}; 

	TrafficLightColour* currentLight[3]; //creating a pointer in an array form to store all the structs at once  
	int currentIndex = 0 ;
	TrafficLight(): currentLight{ &red, &green, &yellow}, currentIndex(0) {} ; //Allowing it to acess each struct address through numbers 
	void displayLight(){
		cout << "Light : " << currentLight[currentIndex]->colour  << endl; 
		this_thread::sleep_for(chrono::seconds(currentLight[currentIndex]->timer)); 
		
	}

	void changeLight(){
		
		currentIndex = (currentIndex + 1) % 3 ; 
	}
	void trafficLightTimer(){
		while(true){
			
			displayLight(); 
			changeLight(); 
		}
	}	

};
int main (){
	TrafficLight TrafficLight; 
	TrafficLight.trafficLightTimer(); 	
	return 0 ;
}
