#include <iostream>
#include <fstream>
#include <windows.h>


using namespace std;


class Voice {
public:
    void say(string phrase);    // Used to textually and audibly communicate a phrase
};

void Voice::say(string phrase){
    string command = "espeak \"" + phrase + "\"";    // Concat the phrase to the command
    const char* charCommand = command.c_str();    // Convert to a const char*
    cout << phrase << endl;    // Textually output phrase
    system(charCommand);    // Send the command to cmd to execute espeak with the phrase an argument
}

class Learner {
public:
    void respond(string phrase);    // Used to get, or teach a response
    void say(string phrase);    // Used to textually and audibly communicate a phrase

    Voice voice;    // The learner's voice that will audibly communicate a response
};

void Learner::respond(string phrase){
    fstream memory;
    memory.open("memory.txt", ios::in);    // Open the memory file for input

    // Search through the file until the end is reached
    while( !memory.eof() ){    // While not at end of file
        string identifier;
        getline(memory,identifier);    // Get next phrase

        if(identifier == phrase){    // Is it the phrase we are looking for
            string response;
            getline(memory,response);   // If so, get the response
            voice.say(response);   // Textually and audibly output the response!
            return;    // Leave the function
        }
    }

    memory.close();    // Looks like we couldn't find the phrase in memory. Close the file!
    memory.open("memory/memory.txt", ios::out | ios::app);    // Now open for output, and append at end of file
    memory << phrase << endl;    // Record initial phrase in memory

    voice.say(phrase);   // Repeat the phrase the user entered
    string userResponse;
    cout << "YOU: ";
    getline(cin, userResponse);    // Get the ideal response
    memory << userResponse << endl;    // Write the ideal response to memory
    memory.close();    // Close the file!
}

/*
    This function simply communicates a phrase textually and audibly
*/
void Learner::say(string phrase){
    this->voice.say(phrase);
}


int main(){
    Learner AI;    // Create a learner object

    /*
    	The following is the main loop. It will continue until the application is closed.
    	The user enters their input, and then the learner will respond.
    */
    for(;;){
        cout << "\nYOU: ";    // User prompt
        string phrase;
        getline(cin, phrase);    // Using getline for multi word input, then store in phrase.

        cout << "COMPUTER: ";
        AI.respond(phrase);    // Pass the user input to the learner and see if he can respond
    }
}

