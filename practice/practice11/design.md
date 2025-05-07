Create a program which tracks a list of board games alongside how many copies exist.
Track how many copies are currently held, and how many have been checked out to customers. 
Manage checking out games to customers and returning them. 
While a game is checked out, keep track of who has it and when it is due back.

class Customer
{
    std::string customerName; //tracking the name of who has it 
    std::string dueDate; //date their game is due to be returned
}

class Game
{
private:
    std::string name;
    int totalCopies; 
    int lentCopies;
    std::vector<Customer> customersBorrowing;
public:
    void lendGame();
    void returnGame();
}




class GameList 
{
private:
    std::vector<Game> gameList;
public:
    void addGame();
}