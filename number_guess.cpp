#include <iostream>
#include <string> 
#include <cstdlib> 
#include <ctime>
#include <string.h>
#include <stdio.h>
using namespace std;

// Display class to handle various outputs to the console, like rules, messages, and formatting
class Display
{
public:
    void printMessageCenter(const char* message); // Function to print messages in the center of the console
    void headMessage(const char *message); // Function to print the header of each game section
    void welcomeMessage(); // Function to display the welcome message
    void drawLine(int n, char symbol); // Function to draw a line with a specific symbol
    void rules(); // Function to display the game rules
};

// Draws a line of length 'n' with the given 'symbol'
void Display::drawLine(int n, char symbol)
{
    for(int i=0; i<n; i++)
        cout << symbol;
    cout << "\n" ;
}

// Displays the rules of the game
void Display::rules()
{
    headMessage("RULES OF THE GAME");
    cout << "\n\n\n\n";
    drawLine(80,'-');
    cout << "\t1. Choose any number between 1 to 10\n";
    cout << "\t2. If you win you will get 10 times of money you bet\n";
    cout << "\t3. If you bet on wrong number you will lose your betting amount\n\n";
    drawLine(80,'-');
    cout << "\n\n\n\t\t\t Enter any key to continue.....";
    getchar(); // Pauses to allow the player to read the rules
}

// Prints a message centered in the console
void Display::printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    len = (78 - strlen(message))/2; // Calculates spaces needed to center the message
    cout << "\t\t\t";
    for(pos =0 ; pos < len ; pos++)
    {
        cout <<" ";
    }
    cout << message;
}

// Prints the header with a given message
void Display::headMessage(const char *message)
{
    system("cls"); // Clears the screen
    cout << "\t\t\t###########################################################################";
    cout << "\n\t\t\t############                                                   ############";
    cout << "\n\t\t\t############             Casino Game Project in C++            ############";
    cout << "\n\t\t\t############                                                   ############";
    cout << "\n\t\t\t###########################################################################";
    cout << "\n\t\t\t---------------------------------------------------------------------------\n";
    printMessageCenter(message);
    cout << "\n\t\t\t----------------------------------------------------------------------------";
}

// Displays the welcome message at the beginning of the game
void Display::welcomeMessage()
{
    headMessage("www.aticleworld.com");
    cout << "\n\n\n\n\n";
    cout << "\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\t\t\t        =                                           =";
    cout << "\n\t\t\t        =                    WELCOME                =";
    cout << "\n\t\t\t        =                      TO                   =";
    cout << "\n\t\t\t        =                 CASINO GAME               =";
    cout << "\n\t\t\t        =                                           =";
    cout << "\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\n\n\t\t\t Enter any key to continue.....";
    getchar(); // Waits for the player to press any key
}

// PlayerInfo class manages the player's details such as betting amount, guess number, etc.
class PlayerInfo:public Display
{
public:
    int getGuessNumber(); // Returns the player's guessed number
    void setGuessNumber(); // Sets the player's guessed number
    void setAmount(); // Sets the player's deposit amount
    float getAmount(); // Returns the player's current balance
    int getdice(); // Generates and returns a random number (1 to 10) to simulate the dice roll
    void updateAmount(const bool isWin); // Updates the player's balance based on win or loss
    void setBettingAmount(); // Sets the amount of money the player wants to bet
    bool isPlayerWin(); // Checks if the player's guess matches the dice roll
    void init(); // Initializes the game by displaying welcome message and rules
    void displayMessageAfterPlay(const bool isWin); // Displays the result of the game after each round
    PlayerInfo():m_amount(0.00),m_bettingAmount(0.00),m_guessNumber(-1)
    {
    }
private:
    float m_amount; // Player's current balance
    float m_bettingAmount; // The amount of money the player bets
    int m_guessNumber; // The number the player guesses
};

// Asks the player to set the deposit amount and validates the input
void PlayerInfo::setAmount()
{
    headMessage("Set Amount");
    do
    {
        cout << "\n\nEnter Deposit amount to play game : $";
        cin >> m_amount;
        if(m_amount < 0.01f) // Ensures the player enters a valid amount
        {
            cout << "\n\nPlease Enter valid amount to play the Game!!";
        }
    }
    while(m_amount < 0.01f);
}

// Returns the player's current balance
float PlayerInfo::getAmount()
{
    return m_amount;
}

// Returns the player's guessed number
int PlayerInfo::getGuessNumber()
{
    return m_guessNumber;
}

// Asks the player to guess a number between 1 and 10 and validates the input
void PlayerInfo::setGuessNumber()
{
    headMessage("Set Guess Number");
    do
    {
        cout << "\n\nGuess your number to bet between 1 to 10 :";
        cin >> m_guessNumber;
        if(m_guessNumber <= 0 || m_guessNumber > 10) // Ensures the guess is between 1 and 10
            cout << "\n\nPlease check the number!! should be between 1 to 10\n"
                 <<"\nRe-enter the number\n ";
    }
    while(m_guessNumber <= 0 || m_guessNumber > 10);
}

// Updates the player's balance based on whether they win or lose
void PlayerInfo::updateAmount(const bool isWin)
{
    m_amount = isWin ? (m_amount + (m_bettingAmount *10)): (m_amount - m_bettingAmount); // If the player wins, they get 10x their bet
}

// Asks the player to set a betting amount and ensures it does not exceed their current balance
void PlayerInfo::setBettingAmount()
{
    headMessage("Set Bet Amount");
    do
    {
        cout <<"\n\nEnter money to bet : $";
        cin >> m_bettingAmount;
        if(m_bettingAmount > m_amount) // Checks if the betting amount is greater than the player's current balance
        {
            cout << "\n\nYour wallet amount is $" << m_amount;
            cout << "\n\nYour betting amount is more than your current balance";
        }
    }
    while(m_bettingAmount > m_amount);
}

// Simulates rolling a dice and checks if the player's guess matches the dice roll
bool PlayerInfo::isPlayerWin()
{
    const int dice = rand()%10 + 1; // Generates a random number between 1 and 10
    return ((dice == getGuessNumber())? true:false); // Returns true if the player guessed correctly
}

// Initializes the game by showing welcome message, setting random seed, and displaying the rules
void PlayerInfo::init()
{
    welcomeMessage();
    srand(time(0)); // Seed for random number generation
    rules();
}

// Displays the result of the game (win/loss) and updates the player's balance
void PlayerInfo::displayMessageAfterPlay(const bool isWin)
{
    if(isWin)
    {
        cout << "\n\nGood Luck!! You won $" << m_bettingAmount * 10;
        cout << "\n\nNow updated Amount is $" << m_amount;
    }
    else
    {
        cout << "\n\nBad Luck this time !! You lost $"<< m_bettingAmount <<"\n";
        cout << "\n\nNow updated Amount is $" << m_amount;
    }
}

// Main function to start the game
int main()
{
    class PlayerInfo obj_player ; // Create a PlayerInfo object
    char choice; // To store the player's choice of continuing the game
    obj_player.init(); // Initialize the game
    obj_player.setAmount(); // Ask the player to deposit an initial amount

    do
    {
        cout << "\n\nYour current balance is $" << obj_player.getAmount() << "\n";
        obj_player.setBettingAmount(); // Set the betting amount
        obj_player.setGuessNumber(); // Set the guessed number
        const bool isPlayerWin = obj_player.isPlayerWin(); // Check if the player wins
        obj_player.updateAmount(isPlayerWin); // Update the player's balance
        obj_player.displayMessageAfterPlay(isPlayerWin); // Display win/loss message

        // If the player runs out of money, end the game
        if(obj_player.getAmount() == 0.00f)
        {
            cout << "You have no money to play, Good Bye..";
            break;
        }

        // Ask if the player wants to play again
        cout << "\n\n-->Do you want to play again (y/n)? ";
        cin >> choice;
    }
    while(choice =='Y'|| choice=='y'); // Continue if the player chooses 'Y' or 'y'

    // End of game messages
    cout << "\n\n\n";
    obj_player.drawLine(70,'=');
    cout << "\n\nThanks for playing game. Your balance amount is $" << obj_player.getAmount() << "\n\n";
    obj_player.drawLine(70,'=');

    return 0;
}