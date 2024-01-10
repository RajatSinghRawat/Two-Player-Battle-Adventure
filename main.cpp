#include <iostream>
using namespace std;

class ToolKit
{
  private:
  //member variable
  int randomNumber;

  public:
  //constructor
  ToolKit()
  {
    randomNumber = 0;
    srand(time(0));
  }

  //member function
  int randomNumberGenerator(int min_Value, int max_Value)
  {
    // Generating random number between given 2 values
    randomNumber = ((rand() % (max_Value - min_Value + 1)) + min_Value);
    return randomNumber;
  }

  //destructor
  ~ToolKit()
  {} 
};

class Player
{
  private:
  //member variables
  int health, initialHealth, damage, min_additionalDamage, max_additionalDamage, min_heal, max_heal, playerNum, probabilityThreshold;

  string playerName;

  public:
  //vitual functions
  virtual void TakeDamage(Player *damageGiver, Player *damageReceiver) = 0;
  virtual int GiveAdditionalDamage(Player *damageReceiver) = 0;


  //member functions
  void showPlayerStats()  
  {
    cout << "Player Health: " << health << endl;
    cout << "Base Damage: " << damage << endl;
    cout << "Additional Damage: " << min_additionalDamage << " - " << max_additionalDamage << endl;
    cout << "Healing Capacity: " << min_heal << " - " << max_heal << endl;
    cout << "------------------------------" << endl;
  }

  void Heal(int heal)
  {
    if(GetHealth() == getInitialHealth())
    {
      cout << "" << GetPlayerName() << "'s(Player " << getPlayerNum() << ") health is already full.";
      cout << "No requirement of healing..!!" << endl;
      cout << "Player " << getPlayerNum() << "'s health: " << GetHealth() << endl << endl;
    }
    else
    {
      cout << "" << GetPlayerName() << "(Player " << getPlayerNum() <<") is using its ability to heal." << endl;
      cout << "Player " << getPlayerNum() <<" is healed by " << heal << "." << endl;
      (GetHealth() + heal) > getInitialHealth() ? 
        SetHealth(getInitialHealth()) : 
        SetHealth(GetHealth() + heal);
      cout << "Player " << getPlayerNum() <<"'s Health after healing: " << GetHealth() << endl << endl;
    }
  }

  void showDamageStats(int damage, int additionalDamage, string attackerName, int attackerNumber)
  {
    cout << "Additional Damage Given: " << additionalDamage << endl;
    cout << "Total Damage Given by Player " << attackerNumber <<": " << damage + additionalDamage << endl; 
    cout << "Remaining Health of Player " << getPlayerNum() << " after receiving damage: " << (isAlive()?
      GetHealth():
      0) << endl << endl;
  }

  bool isAlive()
  {
    if(health > 0)
    {
      return true;
    }
      return false;
  }

  //getters
  int GetHealth()
  {
    return health;
  }

  int GetDamage()
  {
    return damage;
  }

  int getPlayerNum()
  {
    return playerNum;
  }

  int GetMinHeal()
  {
    return min_heal;
  }

  int GetMaxHeal()
  {
    return max_heal;
  }

  int GetMinAdditionalDamage()
  {
    return min_additionalDamage;
  }

  int GetMaxAdditionalDamage()
  {
    return max_additionalDamage;
  }

  int getInitialHealth()
  {
    return initialHealth;
  }

  string GetPlayerName()
  {
    return playerName;
  }

  int getProbabilityThreshold()
  {
    return probabilityThreshold;
  }

  //setters
  void SetHealth(int _health)
  {
    health =  _health;
  }

  //base class constructor
  Player(int health, int damage, int min_additionalDamage, int max_additionalDamage, int min_heal, int max_heal, int playerNum, string playerName, int probabilityThreshold)
  {
    this->health = health;
    this->initialHealth = health;
    this->damage = damage;
    this->min_additionalDamage = min_additionalDamage;
    this->max_additionalDamage = max_additionalDamage;
    this->min_heal = min_heal;
    this->max_heal = max_heal;
    this->playerNum = playerNum;
    this->playerName = playerName;
    this->probabilityThreshold = probabilityThreshold;
  }  

  //base class destructor
  virtual ~Player()
  {
    if(isAlive())
    {
        cout << "!!!!!----------Game Over----------!!!!!" << endl << endl;
    }
    else
    {
      SetHealth(0);  
    }   
  }
};

class HealthyPlayer : public Player, public ToolKit
{
  private:
  //member variables
  int additionalDamage, temporaryDamage, randomNumber;
public:
  //constructor
  HealthyPlayer(int health, int damage, int min_additionalDamage, int max_additionalDamage, int min_heal, int max_heal, int playerNum, string playerName, int probabilityPercent) : Player(health, damage, min_additionalDamage, max_additionalDamage, min_heal, max_heal, playerNum, playerName, probabilityPercent)
  {
    cout << "Hi.. I am a Healthy Player..! Thanks for choosing me." << endl;
    showPlayerStats();    
  } 

  //Implementation of Take Damage Function
  void TakeDamage(Player *damageGiver, Player *damageReceiver)
  {
     cout << GetPlayerName() << "(Player " << getPlayerNum() <<") is taking damage by " << damageGiver->GetPlayerName() << "(Player " << damageGiver->getPlayerNum() << ")." << endl;   
    temporaryDamage = damageGiver->GetDamage();
    additionalDamage = damageGiver->GiveAdditionalDamage(damageReceiver);

    if(getProbabilityThreshold()>=randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! Healthy Player used its special ability to observe least amount of damage." << endl;
      randomNumber = randomNumberGenerator(30,40);
      temporaryDamage = (temporaryDamage * randomNumber)/100;
      additionalDamage = (additionalDamage * randomNumber)/100;
    }

    SetHealth(GetHealth() - (temporaryDamage + additionalDamage));
    showDamageStats(temporaryDamage, additionalDamage, damageGiver->GetPlayerName(), damageGiver->getPlayerNum());

  }

  //Implementation of Give Additional Damage Function
  int GiveAdditionalDamage(Player *damageReceiver)
  {
    if(getProbabilityThreshold()>=randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! Healthy Player used its special ability to do 20% damage as additional damage to other player and also do 20% healing to itself." << endl;

      additionalDamage = (damageReceiver->GetHealth()*20)/100;    
      Heal((GetHealth()*20)/100);          
    }
    else
    {
      additionalDamage = randomNumberGenerator(GetMinAdditionalDamage(), GetMaxAdditionalDamage());
    }
    return additionalDamage;  
  }

  //destructor
  ~HealthyPlayer()
  {   
    isAlive() ? 
      cout << "HealthyPlayer(Player " << getPlayerNum() << ") Wins." << endl << endl : 
      cout << "HealthyPlayer(Player " << getPlayerNum() << ") is Dead." << endl;    
  }    
};

class AveragePlayer : public Player, public ToolKit
{
  private:
  //member variables
  int additionalDamage, temporaryDamage;
  public:
  //constructor
  AveragePlayer(int health, int damage, int min_additionalDamage, int max_additionalDamage, int min_heal, int max_heal, int playerNum, string playerName, int probabilityPercent) : Player(health, damage, min_additionalDamage, max_additionalDamage, min_heal, max_heal, playerNum, playerName, probabilityPercent)
  {
    cout << "Hi.. I am an Average Player..! Thanks for choosing me." << endl;
    showPlayerStats();   
  }

  //Implementation of Take Damage Function
  void TakeDamage(Player *damageGiver, Player *damageReceiver)
  {
    cout << GetPlayerName() << "(Player " << getPlayerNum() <<") is taking damage by " << damageGiver->GetPlayerName() << "(Player " << damageGiver->getPlayerNum() << ")." << endl;

    temporaryDamage = damageGiver->GetDamage();
    additionalDamage = damageGiver->GiveAdditionalDamage(damageReceiver);

    if(getProbabilityThreshold()>=randomNumberGenerator(0, 100))
    {
      temporaryDamage = 0;
      additionalDamage = 0; 
      cout << endl;
      cout << "Woooooh! Average Player used its special ability to fully block the attack." << endl;   
    }

    SetHealth(GetHealth() - (temporaryDamage + additionalDamage));
    showDamageStats( temporaryDamage, additionalDamage, damageGiver->GetPlayerName(), damageGiver->getPlayerNum());
  }

  //Implementation of Give Additional Damage Function
  int GiveAdditionalDamage(Player *damageReceiver)
  {
    additionalDamage = randomNumberGenerator(GetMinAdditionalDamage(), GetMaxAdditionalDamage());

    if(getProbabilityThreshold()>=randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! Average Player used its special ability to give 2X Additional Damage to " << damageReceiver->GetPlayerName() << "(Player " << damageReceiver->getPlayerNum() << ")" << endl;
      additionalDamage = additionalDamage*2;           
    }
      return additionalDamage;  
  }

  //destructor
  ~AveragePlayer()
  {   
    isAlive() ? 
      cout << "AveragePlayer(Player " << getPlayerNum() << ") Wins." << endl << endl : 
      cout << "AveragePlayer(Player " << getPlayerNum() << ") is Dead." << endl;   
  }
};

class AttackingPlayer : public Player, public ToolKit
{
  private:
  //member variables
  int additionalDamage, temporaryDamage;
  public:
  //constructor
  AttackingPlayer(int health, int damage, int min_additionalDamage, int max_additionalDamage, int min_heal, int max_heal, int playerNum, string playerName, int probabilityPercent) : Player(health, damage, min_additionalDamage, max_additionalDamage, min_heal, max_heal, playerNum, playerName, probabilityPercent)
  {
    cout << "Hi.. I am an Attacking Player..! Thanks for choosing me." << endl;
    showPlayerStats();
  }

  //Implementation of Take Damage Function
  void TakeDamage(Player *damageGiver, Player *damageReceiver)
  {
    cout << GetPlayerName() << "(Player " << getPlayerNum() <<") is taking damage by " << damageGiver->GetPlayerName() << "(Player " << damageGiver->getPlayerNum() << ")." << endl;

    temporaryDamage = damageGiver->GetDamage();
    additionalDamage = damageGiver->GiveAdditionalDamage(damageReceiver);

    if(getProbabilityThreshold()>=randomNumberGenerator(0, 100))
    {
      cout << endl;
      cout << "Woooooh! Attacking Player used its special ability to receive half of the attack and bounce back the remaining half attack to the attacker." << endl;
      temporaryDamage = temporaryDamage/2;
      additionalDamage = damageGiver->GiveAdditionalDamage(damageReceiver)/2;
      damageGiver->SetHealth(damageGiver->GetHealth()-(temporaryDamage + additionalDamage));
      cout << "Remaining health of " << damageGiver->GetPlayerName() << "(Player " << damageGiver->getPlayerNum() <<") after receiving bounce back attack: " << damageGiver->GetHealth() << endl;
    }
    SetHealth(GetHealth() - (temporaryDamage + additionalDamage));
    showDamageStats( temporaryDamage, additionalDamage, damageGiver->GetPlayerName(), damageGiver->getPlayerNum());
  }

  //Implementation of Give Additional Damage Function
  int GiveAdditionalDamage(Player *damageReceiver)
  {
    additionalDamage = randomNumberGenerator(GetMinAdditionalDamage(), GetMaxAdditionalDamage());

    if(getProbabilityThreshold()>=randomNumberGenerator(0, 100))
    {      
      cout << endl;
      cout << "Woooooh! Attacking Player used its special ability to do additional damage equal to half of the remaining health of the other player." << endl;
      additionalDamage = damageReceiver->GetHealth()/2;                
    }

    return additionalDamage;  
  }

  //destructor
  ~AttackingPlayer()
  {    
    isAlive() ? 
      cout << "AttackingPlayer(Player " << getPlayerNum() << ") Wins." << endl << endl: 
      cout << "AttackingPlayer(Player " << getPlayerNum() << ") is Dead." << endl;   
  }
};

class GameManager
{
  //member variables
  private:
  enum Players{Player1=1, Player2=2};
  ToolKit *toolkit_obj = NULL;

  Player *player1 = NULL;
  Player *player2 = NULL;

  //for switching between players
  Player *temporaryPlayer = NULL;

  char playerInput;  
  char playerSelectionChoice;
  char playerChoice;

  //assigned all the variables at one place to make easy for the user to change the values

  int probabilityPerecnt = 20;

  string healthyPlayerDisplayName = "Healthy Player";
  string averagePlayerDisplayName = "Average Player";
  string attackingPlayerDisplayName = "Attacking Player";

  int healthyPlayerHealth = 200, healthyPlayerDamage = 10;
  int averagePlayerHealth = 150, averagePlayerDamage = 20;
  int attackingPlayerHealth = 100, attackingPlayerDamage = 30;

  int min_healthyPlayerDamage = 10;
  int max_healthyPlayerDamage = 20;
  int min_healthyPlayerHeal = 30;
  int max_healthyPlayerHeal = 40;

  int min_averagePlayerDamage = 20;
  int max_averagePlayerDamage = 30;
  int min_averagePlayerHeal = 20;
  int max_averagePlayerHeal = 30;

  int min_attackingPlayerDamage = 30;
  int max_attackingPlayerDamage = 40;
  int min_attackingPlayerHeal = 10;
  int max_attackingPlayerHeal = 20;

  public:
  //constructor
  GameManager()
  {
    cout << " -- WELCOME TO 2 PLAYER BATTLE ADVENTURE GAME -- " << endl;
  }

  //Game Intro
  void GameIntro()
  {
      cout << "\nRules For Playing The Game: " << endl;
      cout << "1. Each Player has only one turn at a time." << endl;
      cout << "2. Each Type Of Player has different Health, Damage, Additional Damage and Healing Capacity." << endl;
      cout << "3. Each Player has two options in each turn: Either to do the damage to other Player or Heal yourself" << endl;
      cout << "4. When one's health reaches zero, the other player is the winner." << endl;
      cout << "5. Press 'H' to heal yourself and 'D' to do Damage to other Player" << endl << endl << endl;

      cout << "We have 3 talented players for you to choose from: " << endl << endl << endl;

      cout << "1. Healthy Player:  Who has High Health, Low damage, High healing and Low Additional Damage." << endl;
      cout << "Special Abilities: 1) Receive least amount of damage    2) Do 20% damage as additional damage to other player and also do 20% healing" << endl << endl;

      cout << "2. Average Player:  Who has Average Health, Average damage, Average healing and Average Additional Damage." << endl;
      cout << "Special Abilities: 1) Fully block the attack    2) Give 2X additional damage to the attacker" << endl << endl;

      cout << "3. Attacking Player:  Who has Low Health, High damage, Low Healing and Very High Additional Damage." << endl;
      cout << "Special Abilities: 1) Receive half damage and bounce back remaining half damage to the attacker    2) Do additional damage equal to half of the remaining health of the other player" << endl << endl;

      cout << "NOTE: Each Special Ability has a probability of 20%." << endl << endl;
  }

  //Start Game Loop
  void StartGame()
  {    
    toolkit_obj = new ToolKit();
    GameIntro();
    do
      {  
        player1 = SelectPlayerType(player1, Player1);
        player2 = SelectPlayerType(player2, Player2);

        while(player1->isAlive()  && player2->isAlive())
        {
          PlayerTurn(player1, player2);
          temporaryPlayer = player1;
          player1 = player2;
          player2 = temporaryPlayer;          
        } 
          player1->GetHealth() < player2->GetHealth()?
            (delete player1, delete player2):
            (delete player2, delete player1);

        cout << "Do you want to play again? (Y/N): ";
        cin >> playerChoice;
        cout << endl;

      }while(playerChoice == 'Y' || playerChoice == 'y');  

    delete toolkit_obj;
  }

  //Select a Type of Player
  Player* SelectPlayerType(Player *p, Players playerNum)
  { 
    cout << "Hey Player " << playerNum << endl;
    cout << "Select Your Player Type: " << endl;    
    cout << "Press 1 for Healthy Player, 2 for Average Player and 3 for Attacking Player:" << endl; 
    cin >> playerSelectionChoice;

    while(playerSelectionChoice!='1' && playerSelectionChoice!='2' && playerSelectionChoice!='3')
    {
      cout << "Invalid Input. Please select a valid option." << endl;
      cout << "Press 1 for Healthy Player, 2 for Average Player and 3 for Attacking Player:" << endl;
      cin >> playerSelectionChoice;
    }

    switch(playerSelectionChoice)
    {
      case '1':
      p = new HealthyPlayer(healthyPlayerHealth, healthyPlayerDamage, min_healthyPlayerDamage, max_healthyPlayerDamage, min_healthyPlayerHeal, max_healthyPlayerHeal, playerNum, healthyPlayerDisplayName, probabilityPerecnt);

      break;
      case '2':
      p = new AveragePlayer(averagePlayerHealth, averagePlayerDamage, min_averagePlayerDamage, max_averagePlayerDamage, min_averagePlayerHeal, max_averagePlayerHeal, playerNum, averagePlayerDisplayName, probabilityPerecnt);

      break;
      case '3':
      p = new AttackingPlayer(attackingPlayerHealth, attackingPlayerDamage, min_attackingPlayerDamage, max_attackingPlayerDamage, min_attackingPlayerHeal, max_attackingPlayerHeal, playerNum, attackingPlayerDisplayName, probabilityPerecnt);
      break;      
    }
    return p;
  }

  //In-Game Player Turn
  void PlayerTurn(Player *playing, Player *played)
  {   
    cout << "Player " << playing->getPlayerNum() << "'s Turn: " << endl;
    GetPlayerInput(playing, played);   
  }

  //Getting the Input from Player
  void GetPlayerInput(Player *playing, Player *played)
  { 
    cout << "Press H to heal yourself or D to do Damage to other Player" << endl;
    cin >> playerInput;   
    if(playerInput == 'H' || playerInput == 'h')
    {      
      cout << "You have chosen to heal yourself." << endl;
      playing->Heal(toolkit_obj->randomNumberGenerator(playing->GetMinHeal(), playing->GetMaxHeal()));
    }
    else if(playerInput == 'D' || playerInput == 'd')
    {
      cout << "You have chosen to attack other Player." << endl;
      played->TakeDamage(playing, played);
    }
    else
    {
      cout << "Invalid Input. Please select a valid option." << endl;
      GetPlayerInput( playing, played);
    }
  } 

  //destructor
  ~GameManager()
  {
    cout << "---------THANK YOU FOR PLAYING THE GAME---------" << endl;
    cout << "!!!!-----------SEE YOU AGAIN SOON-----------!!!!" << endl;
  }
};

int main() 
{  
  GameManager *gamemanager_obj = new GameManager();
  gamemanager_obj->StartGame();
  delete gamemanager_obj;
  return 0;
}