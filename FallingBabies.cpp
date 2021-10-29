#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHSD.h"
#include "FEHUtility.h"
#include "LCDColors.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "iostream"
#include "fstream"
using namespace std;

/* Final Design Project for FEH 1281.01 (Dr.Harper 10:20)
Created by Toby Williams, Matthew Wong, and Janet Ann Purtell
Game: Save the Babies*/


 /*This is a Class that holds data for the user.  Its public members are functions that determine aspects
 such as user statisitics, drawing and moving the user character, determining if the user caught a 
 falling object, the useres post game decision (repaly) etc.  The public members also include variables that
 hold information such as user position, where the user has clicked and other key statistics that need to
 be easily accessed by the functions.  Private members include other variables that do not need to be as 
 readily referenced.  (See specific comments for function and varaible purposes/descriptions) 
 -Classes were made together as a group to keep variables consistent*/
  class User
 {
    public:
      User(); //User constructor function
      void UserCharacter(int, int); //draws the user character
      void UserStatsSet(); //sets the inital user statistics to zero
      int UserUpdate(int, int); //updates the user score and lives
      void UserStatsDisplay();// displays active user stats to screen during game play
      void UserMove(); //alows user to move
      void ObjectCaught(int, int); //determines if an object is caught
      void EndGame(); //shows end game screen
      void EndGameDecision(); //returns player to main menu when player clicks appropriate button

      int UserClick_x; // x position of user click
      int UserClick_y; //y position of user click
      int LivesSavedHighScore=0; //high score
      int Score=0; //current score of the user in a specific game
      int LivesLost=0; //how many lives the user has lost
      int TotalLivesLost=0; //total lives the user has lost
      int LivesLeft; //how many lives the user has left in a given game
      int GameDecision=0; //determines whether to return to main menu at the end of the game
      int UserPosition_x;//x position of user character
      int UserPosition_y;//y position of user character
     
     float SurvivalTime; //how long a user has survived
     float SurvivalTimeEnd; //start time of game
     float SurvivalTimeStart; //end time of game
     float SurvivalTimeHighScore=0; //highest survival time over several games

    private:
      int UserLeft=-12; //how far the user moves left when left button is pressed
      int UserRight=12; //how far the user moves right when right button is pressed
      int Alive=1; //determines if user is alive
      int PreviousLivesScore=0; //keeps track of previous score
      int PreviousLivesLost=0; //keeps track of previous lives lost
      
 }; 

/*This class contians datd for the game environment.  It has public functions that draw things like the 
 ground plane, left/right buttons and other stationary elements of the game environment. It also has public 
 variables which are need to be easily accessed.  There are no private elements to this class.  (See
 specific comments for function and varaible purposes/descriptions)
 -Classes were made together as a group to keep variables consistent */
 class Environment
 {
     public:
    
     int ReturnMenu_button(); //returns to amin menu when clicked
     void DrawUser(); //draws user at initial position
     void DrawButtons();// draw left/right button
     void DrawGround(); //draw ground plane
     void DrawBuildings(); //draw buildings on side
     void DrawLives(); //draw heart icon on screen where lives statistic will be diplayed
     void DrawScore(); //draw score icon on screen where score statistic will be displayed
     void DrawFire(int); //draw fire on buildings
     int i; //loop index for drawing heart icon
     int x = 240, y = 232, length = 1; //variables to define position of heart icon on playing screen

 };

/*This Class hold data related to the main menu.  It contains public functions that draw the menu
 diplay statistics in the menu, dipaly credits, and the plot/instruction to the game.  There are no
 private members of this class.
 -Classes were made together as a group to keep variables consistent */
 class Menu
 {
     public:
     void DisplayMenuStats(int, int, float); //display statistics to screen under statistics tab 
     void DisplayCredits();// display credits under credits tab
     void DisplayPlot1(); //display plot/instructions under the plot/overview tab
     void DrawMenu();// draw the main menu screen

 };


/*This is a class that holds data for the various types of falling objects in the game.  It includes
public member functions such as a deconstuctor function, functions that generate objects, draw specific
objects, make an object fall, decide if an object hit the user, decide if an object hitting the user will
gain or loses points/lives, etc.  The public variables include the position of a randomly generated object,
an identifier for that object, a varaible keeping track of whether a given object is still in play, the 
bounds to where an object can be generated etc. There is one private variable which is used in detriming the type of 
random object generated. (See specific comments for function and varaible purposes/descriptions)
-Classes were made together as a group to keep variables consistent*/
 class FallingObjects {

    public:
        //The following website was used to help understand a deconstuctor function for our purposes
        //https://www.tutorialspoint.com/cplusplus/cpp_constructor_destructor.htm
        ~FallingObjects(){
            }//Deconstructor function to reset falling objects between games

     void GenerateObjects();//generates random objects
     void DrawBaby();// draws baby icon
     void ObjectFall(); //has object fall 10 pixels
     void DrawCoin(); //draws coin icon
     void DrawBox(); //draws box icon
     void Collision(int); //determines if a object collides with user
     void GoodCatch(); // determines if user has caught a baby or a coin
     void BadCatch(); //determines if user has caught a box
     int StatusGoodCatch();//returns if a catch was good
     int StatusBadCatch();//returns if a catch was bad
     
     int PosX, PosY;// x and y positions of randomly generate object
     int ObjectAlive=1; //if true the object can still be move
     
     int Identifier;// identifies the type of object (numeric value assinged to each type)
     int max_x = 270;//x bounds for generation of objects
     int min_x = 50;//x bounds for generation of objects
     
     int UserLifeLost=0; //determines if a life has been lost
     int UserCatch=0; // determines if a catch has been made

    private:
     int randomObj; //type of random object made (numeric value assinged to each type)
         
 }; 


/*The main function was a collaboration between all group memebers and then specific functions were done
on a more individual basis*/ 
int main() {
    
    //Initilize some gameplay variables
    int main_menu = 1;
    int UserAlive;
    int i;
    int ObjectCounter;
    double TimeInitializer;
    float TimeAccel=1.05;
    double runtime;

    //create object 'player' from the user class. This object is used to control the character and its variables.
    User player;

    //Create object 'GameUI' from the Environment Class. This object is used to call function regarding the UI.
    Environment GameUI;

    //Create Object 'MenuUI' from the Menu Class. This object is used to called functions regarding menu interactions.
    Menu MenuUI;


//return from game while loop
while(player.GameDecision==0) {
    main_menu=1;
    
    //start of menu code
    while (main_menu == 1)
    {
        //clear screen
        LCD.Clear();
        //draw Menu UI 
        MenuUI.DrawMenu();
        
        //wait till screen is pressed
        while(!LCD.Touch(&player.UserClick_x, &player.UserClick_y))
        {

        }

        //decide which button is clicked (x direction is same for all buttons)
        if (player.UserClick_x >= 60 && player.UserClick_x <= 260) {

            //Game Run button
            if(player.UserClick_y >= 80 && player.UserClick_y <= 110) {
                
                //set variables to allow for gameplay
                player.GameDecision=1;
                main_menu=0;
                LCD.Clear();
                
            } //end game run button

            //Show stats button
            if(player.UserClick_y >= 120 && player.UserClick_y <= 150){
                    LCD.Clear();
                    //display stats based on public variables from the User Class
                    MenuUI.DisplayMenuStats(player.LivesSavedHighScore, player.TotalLivesLost, player.SurvivalTimeHighScore);

                    //call the main menu button and return value based on click
                    main_menu=GameUI.ReturnMenu_button();
                    
                } //End show stats button

            //plot overview button   
            if(player.UserClick_y >= 160 && player.UserClick_y <= 190){
                    LCD.Clear();
                    //display Plot
                    MenuUI.DisplayPlot1();

                    //call the main menu button and return value based on click
                    main_menu=GameUI.ReturnMenu_button();
                    
                }//end plot overview button
            
            //credits button
            if(player.UserClick_y >= 200 && player.UserClick_y <=230) {
                    LCD.Clear();
                    //Display Credits
                    MenuUI.DisplayCredits();

                    //call the main menu button and return value based on click
                    main_menu= GameUI.ReturnMenu_button();
                }//end credits button

        }//end button if statement for x range       

    }//end main menu loop



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/*                   **** DIVIDER BETWEEN MENU AND GAME CODE ****                         */       
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////





while (player.GameDecision==1) { 

    LCD.ClearBuffer();
    //set stats
    player.UserStatsSet();
    
    //set stats outside of User object
    UserAlive=1;
    ObjectCounter=0;
    TimeInitializer=12;

    //call function in environment class to draw the ground
    GameUI.DrawGround();

    //call function in environment class to draw the left/right buttons
    GameUI.DrawButtons();

    //call function to draw building
    GameUI.DrawBuildings();
    GameUI.DrawFire(290);
    GameUI.DrawFire(10);

    //call functions to draw score and lives icon
    GameUI.DrawLives();
    GameUI.DrawScore();

    //call function to draw user
    player.UserCharacter(player.UserPosition_x, player.UserPosition_y);


    //Generate an array of 300 objects from class FallingObjects
    FallingObjects Object[300];

    //generate the first object
    Object[0].GenerateObjects();



    while (UserAlive==1) {//run loop while player is still alive

        // run if click has happened
        if(LCD.Touch(&(player.UserClick_x), &(player.UserClick_y))){
            LCD.ClearBuffer();
            //Move player position
            player.UserMove();
                
        }  
    
        runtime=TimeNow();

        if (runtime>=TimeInitializer) {
            TimeInitializer=runtime+(4-pow(TimeAccel,ObjectCounter)); //Accelerates rate of which objects whill fall
            ObjectCounter+=1; //increase object counter
            Object[ObjectCounter].GenerateObjects(); //generate new objects based on counter
        }

        for (i=0;i<=ObjectCounter;i++) { //cycle through all objects
            
            if (Object[i].ObjectAlive==1) { //check if object is still alive
                Object[i].ObjectFall(); //call function to move object down
                Object[i].Collision(player.UserPosition_x-4); //call function to determine collision
                UserAlive=player.UserUpdate(Object[i].StatusGoodCatch(), Object[i].StatusBadCatch()); //update stats
                
                if (Object[i].UserCatch==1 || Object[i].UserCatch==2){ //if hit by coin or baby, redraw character
                    player.UserCharacter(player.UserPosition_x, player.UserPosition_y);
                }
                  
            }
            
            player.UserStatsDisplay(); //Display stats to screen
        }
            
    }//End alive loop


    player.EndGame(); //Called if player is no longer alive, create end game menu


}//End Overarching run game loop

}//End Return to menu loop

} //End Main function


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/*                   **** DIVIDER BETWEEN GAME CODE AND FUNCTIONS ****                    */       
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/*                              **** START USER FUNCTIONS ****                            */       
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

/*This function is the constructor for the User Class. It initiliazes the user position in both
the x and y coordinates to a specific coordinate. It also initilizes the HighScore to zero. 
- Janet Ann Purtell */

User::User(){
    UserPosition_x=160; 
    UserPosition_y= 201;
    LivesSavedHighScore=0;
}//End constructor function

/*The function UserCharacter within the User Class draws the character. It takes in two 
arguments that correspond to the x and y coordinates of a certain pixel in the character. 
All other drawn pixels are based relative to these coordinates, so when the argument coordinates 
change, all of the drawn pixels respond accordingly. A black rectangle is also drawn to 
delete its previous position when the arguments change. This function is set as void as 
it does not return any values, because it actively draws and erases from the screen. 
The variables x and y are local to just this function alone, and are based off of the 
UserPosition_x and UserPosition_y which are public within the class.
- Janet Ann Purtell*/

void User::UserCharacter(int x,int y) {
    
    //erase guy left
    if(x > 55){
    LCD.SetDrawColor(LCD.Black);
    LCD.FillRectangle(x-15, y-10, 8,13);
    }
    
    //erase guy right
    if(x < 265){
    LCD.SetDrawColor(LCD.Black);
    LCD.FillRectangle(x+9, y-10, 8,13);
    }

    //draw guy
    //body of little guy
    LCD.SetDrawColor(LCD.Red);
    LCD.DrawPixel(x,y);
    LCD.DrawPixel(x, y-1);
    LCD.DrawPixel(x, y-2);
    LCD.DrawPixel(x, y-3);
    LCD.DrawPixel(x, y-4);
    LCD.DrawPixel(x, y-5);
    LCD.DrawPixel(x, y-6);
    LCD.DrawPixel(x, y-7);
    LCD.DrawPixel(x+1,y);
    LCD.DrawPixel(x+1, y-1);
    LCD.DrawPixel(x+1, y-2);
    LCD.DrawPixel(x+1, y-3);
    LCD.DrawPixel(x+1, y-4);
    LCD.DrawPixel(x+1, y-5);
    LCD.DrawPixel(x+1, y-6);
    LCD.DrawPixel(x+1, y-7);
    
    //arms of little guy
    LCD.FillRectangle(x+2, y-5, 3, 2);
    LCD.FillRectangle(x-3, y-5, 3, 2);

    //head of little guy
    LCD.FillRectangle(x-1, y-10,4,3);

    //legs of little guy
    LCD.FillRectangle(x-2, y, 2, 3);
    LCD.FillRectangle(x+2, y, 2,3);
    
    
}//End UserCharacter function


/*The function UserMove within the User class is used to update the characters position
variables if the correct buttons are clicked. This function does not take any parameters, 
as the UserClick variables are in the class. This function also does not return a value,
as the UserPosition variable that are getting updated are in the User Class and are public.
At the end of the function, the user position is updated using the UserCharacter function
within the User class.
-Janet Ann Purtell */

void User::UserMove(){

    //click left button
    if (UserClick_x >= 100 && UserClick_x <=150 ) {//x value of left button
        if (UserClick_y >= 210 && UserClick_y <=235) {// y value of left button
            //increment user position to the left
            UserPosition_x+=UserLeft;
            
            //keep character on screen
            if (UserPosition_x<=50) {
                UserPosition_x=50;
            }
            //set user click to outside the range of the button  
            UserClick_x = 0;
            UserClick_y = 0;  
        }
    }
        //click right button
    if (UserClick_x >= 160 && UserClick_x <=210 ) { //x value right button
        if (UserClick_y >= 210 && UserClick_y <=235) { //y value right button
            //increment user position to the right
            UserPosition_x+=UserRight;

            //keep character on screen
            if (UserPosition_x>=270) {
                UserPosition_x=270;
            }
            //set user click to outside the range of the button  
            UserClick_x = 0;
            UserClick_y = 0;  
        }
    }
    //print player character in new location
    UserCharacter(UserPosition_x, UserPosition_y);

}//End UserMove Function



/*The purpose of the function UserStatsSet within the User Class is to reset some of the 
important public variables in the User class before the start of a new game. 
It is called right as gameplay starts, and records the timestamp at that initialization. 
The function is void as it does not return any values, as it just resets a portion of the 
public variables in the function to their proper start-of- game values.
-Janet Ann Purtell*/

void User::UserStatsSet(){
    
    //reset variables
    Score=0;
    LivesLost=0;
    LivesLeft=5;
    PreviousLivesScore=0;
    PreviousLivesLost=0;
    //start timer
    SurvivalTimeStart=TimeNow();
    
    
}//End UserStatsSet function



/*The function UserUpdate in the User class is used to take in values determined
by the objects in the FallingObject Class and change its own status variables
accordingly. The variables that are changed based on the arguments are the Public Livelost
and Score Variables. It is then determined if Lives lost is more than 5, and if true, the
private variable Alive is set to 0. This function returns the Alive integer to the main program.
-Toby Williams*/
int User::UserUpdate(int GoodCatch, int BadCatch){
    //increment variables based on argument
    LivesLost+=BadCatch;
    Score+=GoodCatch;

    //determine if user is still alive
    if (LivesLost>=5) {
        Alive=0;
    }
    else {
        Alive=1;
    }

    return Alive; //return status to main program

}//End Update Stats function



/*The function UserStatsDisplay within the User class is used to display the current 
score of the user and the current amount of lives left. The function has no arguments, 
as these variables are public in the class. In the main program, this function is 
called constantly, so the display is only updated if changes have occured. This is
done by using the private variables of PreviousLivesScore and PreviousLivesLost. This
function is void because it does not return a value.
-Toby Williams*/

void User::UserStatsDisplay(){

    //determine if changes have occured
    if ((Score > PreviousLivesScore) || (LivesLost > PreviousLivesLost))
    {

        //calculate LiveLeft base off of Liveslost
        LivesLeft = 5 - LivesLost;
        //clear previous stats using rectangle
        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(260, 212, 30, 20);
        LCD.FillRectangle(65, 212, 25, 20);

        //Draw score
        LCD.SetFontColor(LCD.Red);
        LCD.WriteAt(Score, 65, 213);
        
        //display livesleft
        LCD.SetFontColor(LCD.Red);
        LCD.WriteAt(LivesLeft, 260, 213);
        
        //set color back to white
        LCD.SetFontColor(LCD.White);

        //update previous variables
        PreviousLivesScore=Score;
        PreviousLivesLost=LivesLost;

    }

}//End Display stats function



/*The purpose of the EndGame function within the User class is to be called upon when the 
user has lost the game, and to display statistics like Lives lost, the score, and the total
survival time. This function also stops the timer on the game, and draws the return to menu
button. A seperate function is then called to determine if the user has pressed the return 
to menu button. This function is void, as it does not return any values when called. Instead,
it changes several public variables within the User Class, and does some simple calculations.
- Toby Williams*/

void User::EndGame(){
    LCD.Clear();
    

    SurvivalTimeEnd=TimeNow(); //end timer
    SurvivalTime=SurvivalTimeEnd-SurvivalTimeStart; //calculate total time

    TotalLivesLost+=LivesLost; //increment total lives lost
    
    //display stats 
    LCD.SetFontColor(LCD.Red);
    LCD.WriteAt("You Killed too many babies!",50, 40);
    LCD.WriteAt("**Game Stats**", 30, 70);
    LCD.WriteAt("SCORE: ", 30, 90);//Display Lives saved
    LCD.WriteAt(Score, 100, 90);

    //determine if highscore was achieved for lives saved
    if (Score>LivesSavedHighScore) {
        LivesSavedHighScore=Score;
        LCD.WriteAt("HIGHSCORE!", 130, 90);

    }
    
    LCD.WriteAt("Time: ", 30, 110);
    LCD.WriteAt(SurvivalTime, 90, 110);

    //determine if highscore was achieved for survival time
    if (SurvivalTime>SurvivalTimeHighScore){
        SurvivalTimeHighScore=SurvivalTime;
        //Display High Score Graphic
        LCD.WriteAt("HIGHSCORE!", 180, 110);
    }
    
    //return to menu button
    LCD.SetFontColor(LCD.White);
    LCD.SetDrawColor(LCD.Blue);
    LCD.FillRectangle(90, 200, 153, 30);
    LCD.WriteAt("Return Main Menu", 95, 210);
    
    //call function to determine user touch
    EndGameDecision();
    
}//End EndGame function


/*The purpose of the EndGameDecision function inside of the User Class is to determine
if the user has pressed the main menu button, and to change the necessary variables based
on that input. If the button is deemed to have been clicked, the GameDecision variable,
which is a public variables within the user class, is set to zero, which brings the user
back to the main menu. A "wait" variable is also made in this function, which is used if
the user does not click the right position on the screen. This function is set to void
as it does not return any value, as the variable it changes is public.
-Toby Williams*/

void User::EndGameDecision(){
   
    int Wait=1;
    while (Wait==1) {
        LCD.ClearBuffer();

        //wait for touch
        while(!LCD.Touch(&(UserClick_x), &(UserClick_y))) {
        }
        
        //return to main menu button clicked
        if (UserClick_x >= 110 && UserClick_x <=270 ) {
            if (UserClick_y >= 200 && UserClick_x <=230 ) {
                GameDecision=0;
                Wait=0;
            }
        }
        else {
            Wait=1;
        }

    }//End wait loop

LCD.Clear(); //clear screen

} //End Game Decision function


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/*                        **** START FALLINGOBJECTS FUNCTIONS     ****                    */       
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



/* This function has no input arguments as it has access to all needed variables in the Falling Objects
class.  It is meant to generate a random type of object (a baby, a box, a coin) at a random location
within the bounds of user movement.  It also assigns an identifier to each object so that the program 
can later idenify what type of object each object is
-Janet Ann Purtell*/

void FallingObjects::GenerateObjects(){

    //Random number generator for position and type of object
    PosX = (RandInt()%210) + 55;
    PosY=0;
    randomObj =RandInt()%3;
    //Set the object to be alive so it will continue to fall
    ObjectAlive=1;

    //Switch case to assign Idenifier
    switch (randomObj) {
        //For Baby
        case 0:
            Identifier=0;
            DrawBaby();
            break;
        //For Coin    
        case 1:
            Identifier=1;
            DrawCoin();
            break;
        //For Box    
        case 2:
            Identifier=2;
            DrawBox();
            break;
        
    }//End switch

}//End generate falling objects function



/* This function has no inputs as it can acess all needed variables from the class FallingObjects. It 
has no return as it is void.  The function is meant to draw the baby pixel art based on the user position.
The baby fits within a ten by ten square and is draw from a reference point of the upper left corner 
corresponding to the point where the user position is defined. 
- Matthew Wong */
void FallingObjects::DrawBaby(){

    //Use user position (PosX and PosY) to draw baby
    
    //set color to brown
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(PosX+3, PosY, 5, 4);
    LCD.FillRectangle(PosX+3, PosY+9, 2, 1);
    LCD.FillRectangle(PosX+6, PosY+9, 2, 1);
    LCD.DrawPixel(PosX+1, PosY+3);
    LCD.DrawPixel(PosX+9, PosY+3);
    
    //Set color to skyblue
    LCD.SetDrawColor(SKYBLUE);
    LCD.DrawPixel(PosX+1, PosY+4);
    LCD.DrawPixel(PosX+5, PosY+4);
    LCD.DrawPixel(PosX+9, PosY+4);
    LCD.FillRectangle(PosX+1, PosY+5, 9, 1);
    LCD.FillRectangle(PosX+4, PosY+6, 3, 1);
    LCD.FillRectangle(PosX+3, PosY+7, 5, 1);
    LCD.FillRectangle(PosX+3, PosY+8, 2, 1);
    LCD.FillRectangle(PosX+6, PosY+8, 2, 1);

}//End DrawBaby function
 


/* This function has no inputs as it can acess all needed variables from the class FallingObjects. It 
has no return as it is void.  The function is meant to draw the coin pixel art based on the user position.
The coin fits within a ten by ten square and is draw from a reference point of the upper left corner 
corresponding to the point where the user position is defined. 
- Mathew Wong*/

void FallingObjects::DrawCoin(){
    
    //Use user position (PosX and PosY) to draw coin

    //set color to yellow
    LCD.SetDrawColor(YELLOW);
    LCD.FillCircle(PosX + 4, PosY + 4, 4);
    
} //End DrawCoin function



/* This function has no inputs as it can acess all needed variables from the class FallingObjects. It 
has no return as it is void.  The function is meant to draw the box pixel art based on the user position.
The box fits within a ten by ten square and is draw from a reference point of the upper left corner 
corresponding to the point where the user position is defined. 
-Matthew Wong*/

void FallingObjects::DrawBox() {
    
    //Use user position (PosX and PosY) to draw box
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(PosX, PosY, 10, 10);

}//End DrawBox Function



/* This function takes in no arguments as it has access to needed variables in the class FallingObjects.
It is meant to increment the y position of a given objcet down by 10 pixels.  It also acesses an object's
identifier and draws the correct object based on that 
-Toby Williams */
void FallingObjects::ObjectFall(){
    
    //increment y position (object speed)
    PosY+=10;
    
    //For an object idenified as a baby
    if (Identifier==0) {

        //clear screen of previous drawing   
        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(PosX, PosY-10, 10, 10);

        //Draw baby at new position
        DrawBaby();
           
    }

    //For an object identified as a coin
    if (Identifier==1 && PosY < 193) {

        //clear screen of previos drawing
        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(PosX, PosY-13, 10, 13);

        //draw coin at new position
        DrawCoin();           
           
    }

    //For an object identified as a box
    if (Identifier==2 && PosY < 193) {

        //clear screen of previous drawing
        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(PosX, PosY-10, 10, 10);
        
        //Draw box in new poistion
        DrawBox();

    }
      
    //If the object is not a baby and has hit the ground, delete it
     if ((Identifier!=0) && (PosY>=190)) {
        
        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(PosX, PosY-10, 12, 20);

        //Set the object as not alive so it will no longer be incremented
        ObjectAlive=0;
            
     }
    
}//End Object Fall function



/* The purpose of the Collision function inside of the FallingObjects Class is to take in the
x-position of the stick figure and to determine if the current x and y position of the falling
object are within the hitbox bounds of the stick figure. If the falling object is within the 
hitbox bounds, the object's identifier is used to determine what action is now necessary, and
calls the appropriate function. This function has no return values, as its purpose is to 
determine what additional function to call based on the scenario. This function uses the public 
variables in class FallingObjects of PosX, PosY, and Identifier. This functions also contains
the variables x, which is the argument that corresponds to the user position, which is private to
just this function. Written by Toby*/

void FallingObjects::Collision(int x){
    
    if (PosY+10 >= 200) { //determine y range, 200 corresponds to static y value of figure
        if (PosX >= x-10) { //left bound of hitbox
          if (PosX <= x+10) { //right bound of hitbox
            if (Identifier==0){ //Baby Identifier
                GoodCatch();
            
            }
            else if (Identifier==1) { //Coin Identifier
                GoodCatch();
            }
            else { //Box Identifier
                BadCatch(); 
                
            }
          }        
        }
    }
    
    if (Identifier==0) { //Determine if baby hit ground and was not caught
        if ((PosY+10>=204 && UserCatch==0)) {
            BadCatch();
            
        }
    }
        
} //End of Collision Function



/* The purpose of the GoodCatch function inside of the FallingObjects class is set update the  
status of the object if it was determined to be a good catch (aka a coin or baby was caught).
Once called, the function also "deletes" the falling object by covering its current
position with a black rectangle. The function then determines if the object was a coin or a
baby based on its Identifier number, and then increments its UserCatch status by the appropriate
ammount, as coins are worth more to catch than babies. The function also sets the ObjectAlive
variables, which is used to determine if the object should still be actively falling, to 0.
- Toby Williams*/

void FallingObjects::GoodCatch(){
    LCD.SetDrawColor(LCD.Black); //draw coverup rectangle
    LCD.FillRectangle(PosX, PosY-10, 10, 20);
    LCD.SetDrawColor(LCD.Red);
    LCD.DrawHorizontalLine(204, 40, 360);
    LCD.DrawHorizontalLine(205, 40, 360);
    
    ObjectAlive=0; //make object "dead"
    
    if (Identifier==0){//Baby Identifier
        UserCatch=1;
    }
    
    if (Identifier==1){//Coin Identifier
        UserCatch=2;
    }

} //End of GoodCatch function



/* This function is used to return the value of UserCatch, which correlates to the 
ammount of points the objects holds if it was caugh. This is used in int main() to 
give a function of the User class the values determined by the FallingObject Object 
in order to determine the users score.
-Toby Williams */

int FallingObjects::StatusGoodCatch(){
    
    return UserCatch;
}//End StatusGoodCatch function



/* The purpose of the function BadCatch inside the Falling Objects class is to update the
status of the object if it was determined that the object experienced a bad catch, for example
if the box was caught. The object first "deletes" the appearance of the object using a black
rectangle layed over its current position. The object is then set to be no longer alive, meaning
it will no longer undergo movement. It is also set to be deemed to have cost a user life, which
will then get pasted on to other functions that store that info and then decide if the user
is dead or not. 
-Toby Williams*/
void FallingObjects::BadCatch(){
    LCD.SetDrawColor(LCD.Black);
    LCD.FillRectangle(PosX, PosY, 10, 10);

    ObjectAlive=0; //make object "dead"
    UserLifeLost=1; //lost user a life

}// End BadCatch function



/* This function is used to return the value of UserLifeLost, which values correlates
to if the object was deemed to have cost a life. This is used in int main() to give
a function of the User class the values determined by the FallingObject Object in order
to determine if the user is still alive. 
-Toby Williams*/

int FallingObjects::StatusBadCatch(){
    
    return UserLifeLost;
}//End StatusBadCatch function



////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/*                              **** START MENU FUNCTIONS     ****                        */       
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


/*This function is used to draw the main menu.  It prints the title, buttons and lables. Note, none of 
the "buttons" are able to be clicked with this function.  The buttons being clicked is done by if 
statements in the main function within the menue loop. It takes in no input as is has acess to all needed 
variables in the Menu class.  It is void so it has no return. 
-Janet Ann Purtell*/

void Menu::DrawMenu(){
    //Draw Title
    LCD.SetDrawColor(LCD.White);
    LCD.WriteAt("Save the Babies!", 95, 35);

    //set draw color to red
    LCD.SetDrawColor(LCD.Red);

    //draw button rectangles 
    LCD.FillRectangle(60,80,200,30);
    LCD.FillRectangle(60,120,200,30);
    LCD.FillRectangle(60,160,200,30);
    LCD.FillRectangle(60,200,200,30);

    //print button labels
    LCD.SetDrawColor(LCD.White);
    LCD.WriteAt("Start Game!", 105, 85);
    LCD.WriteAt("Game Statistics", 95, 125);
    LCD.WriteAt("Plot/Overview", 95, 165);
    LCD.WriteAt("Credits", 125, 205);

}//End DrawMenu function


/* This function displays the credits of the game.  It is meant to be called after the "Credits"
button is clicked. It takes in no input as is has acess to all needed variables in the Menu class.  
It is void so it has no return.
-Janet Ann Purtell*/

void Menu::DisplayCredits(){
    LCD.WriteLine(" Credits:");
    LCD.WriteLine(" Creators:  Janet Ann Purtell");
    LCD.WriteLine(" Toby Williams, and Matthew Wong");
    LCD.WriteLine(" References:");
    LCD.WriteLine(" - feh.osu.edu");
    LCD.WriteLine(" - www.tutorialspoint.com");
    LCD.WriteLine(" Special thanks to Dr Harper and the FEH");
    LCD.WriteLine(" TAs for teaching us everything we know!");

}//End DisplayCredits function

/* This functions displays the plot/overview of the game along with simple instructions. It is meant
to be called after the "Plot/Overview" button is clicked. It takes in no input as is has acess to all
 needed variables in the Menu class.  It is void so it has no return.
 - Matthew Wong*/

void Menu::DisplayPlot1(){

    //set color to white
    LCD.SetDrawColor(LCD.White);
    //write plot/instructions
    LCD.WriteLine("The local nursery is on fire! If you drop ");
    LCD.WriteLine("a baby or get hit by a box, you lose"); 
    LCD.WriteLine("1 of 5 lives. Catch the coins though for ");
    LCD.WriteLine("Bonus Points! Click the arrows to move!");

    LCD.WriteLine("Baby:");
    LCD.WriteLine("Coin:");
    LCD.WriteLine("Box:");

    //draw to screen the three object icons so the user knows what to look for

    //define the position the baby icon will be drawn on the plot screen
    int x = 50;
    int y = 105;

    //draw example baby icon
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(x+3, y, 5, 4);
    LCD.FillRectangle(x+3, y+9, 2, 1);
    LCD.FillRectangle(x+6, y+9, 2, 1);
    LCD.DrawPixel(x+1, y+3);
    LCD.DrawPixel(x+9, y+3);
    
    LCD.SetDrawColor(SKYBLUE);
    LCD.DrawPixel(x+1, y+4);
    LCD.DrawPixel(x+5, y+4);
    LCD.DrawPixel(x+9, y+4);
    LCD.FillRectangle(x+1, y+5, 9, 1);
    LCD.FillRectangle(x+4, y+6, 3, 1);
    LCD.FillRectangle(x+3, y+7, 5, 1);
    LCD.FillRectangle(x+3, y+8, 2, 1);
    LCD.FillRectangle(x+6, y+8, 2, 1);

    //reset the y value to print the coin icon below the baby icon
    y = 135;
    //draw example coin icon
    LCD.SetDrawColor(YELLOW);
    LCD.FillCircle(x+4, y+4, 4);
    
    //reset the y value to print the box icon below the coin icon
    y = 155;
    //draw example box icon
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(x, y, 10, 10);
    LCD.WriteLine(""); 
    LCD.WriteLine("");

}//End displayplot1 function


/*This function is meant to display to screen the statistics of the user.  This is called after the user 
clicks the Statistics buttonon the main menu.  The function is passed LivesSavedHighScore (the user's
high score), TotalLivesLost (how many lives the have lost over all games plyed), and SurvivalTimeHighScore 
(the time of the longest game the user played) from the "user" class through the object "player".  This 
displays active stats that change between games if the user sets a new high score.  It is void so it 
returns nothing
-Janet Ann Purtell*/

void Menu::DisplayMenuStats(int HighScore,int LivesLost, float SurvivalTimeHighScore) {

    //set color to white
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("HighScore: ", 0, 20);
    //set color to red
    LCD.SetFontColor(LCD.Red);
    //write the highscore to the screen
    LCD.WriteAt(HighScore, 140, 20);

    //set color to white
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("Total Lives Lost: ", 0, 40);
    //set color to red
    LCD.SetFontColor(LCD.Red);
    //write the lives lost to the screen
    LCD.WriteAt(LivesLost, 140, 40);

    //set color to white
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("Longest round: ", 0, 60);
    //set color to red
    LCD.SetFontColor(LCD.Red);
    //write the longest survival time to screen
    LCD.WriteAt(SurvivalTimeHighScore, 140, 60);

    //set color back to white
    LCD.SetFontColor(LCD.White);    


}//End displaymenustats function


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/*                           **** START ENVIRONMENT FUNCTIONS     ****                    */       
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



/* This function prints the return to main menu button and determines if it has been clicked.  It is not
passed any inputs.  It returns a choice variable that is true if the user clicked the main menu button. 
This value is then used in the main function during the main menu loop to determine whether to continue 
displaying the main menu.  This function is called in after pressing any button on the main menu screen
besides the "Play Game" button and ultimatley allows the user to return to the main menu screen after 
clicking those buttons.
- Janet Ann Purtell */
int Environment::ReturnMenu_button() {
    
    //define variables of the x and y position of the user click
    int click_x, click_y;
    //initialize the choice to return to main menu as  false
    int choice=0;
    //initialize a varaible to false that keeps track of if the user clicked in the correct location 
    int click = 0;
    LCD.SetDrawColor(LCD.Blue); //draw main menu button
    LCD.FillRectangle(10, 200, 100, 30);
    LCD.WriteAt("Main Menu", 15, 210);
    
    //while the user has not clicked in the correct location
    while (click == 0) {
         while(!LCD.Touch(&click_x, &click_y))
            {  

            }//wait for user touch
            //determine if click is in x range of button
            if (click_x >= 10 && click_x <=110 ) {
                //determine if click is in y range of button
                if (click_y >= 200 && click_x <=230 ) {
                    //set choice to true
                    choice=1;
                    //set click to true since button has been clicked
                    click=1;
                }
            }//End Return to main menu click
    }//End click while loop   
    
    //clear screen, set color to white, and return the choice 
    LCD.Clear();
    LCD.SetDrawColor(LCD.White);
    return choice;
}//End Return Menu button definition


/*This function draws the buttons for moving left and right in the game environment.  This function
only draws the buttons, not determines if the button has been clicked.It has no input and has no return
since it is void.
- Matthew Wong*/
void Environment::DrawButtons(){
    //left button

    //set draw color to blue and draw rectangle
    LCD.SetDrawColor(LCD.Blue);
    LCD.FillRectangle(100, 210, 50, 25);

    //set color to white and draw left button arrow
    LCD.SetDrawColor(LCD.White);
    LCD.FillRectangle(105,223,8,1);
    LCD.FillRectangle(106,222,7,1);
    LCD.FillRectangle(107,221,6,1);
    LCD.FillRectangle(108,220,5,1);
    LCD.FillRectangle(109,219,4,1);
    LCD.FillRectangle(110,218,4,1);
    LCD.FillRectangle(111,217,3,1);
    LCD.FillRectangle(112,216,2,1);
    LCD.DrawPixel(113,215);
    LCD.SetDrawColor(LCD.White);
    LCD.FillRectangle(113,219, 34,9);
    LCD.FillRectangle(106,224,7,1);
    LCD.FillRectangle(107,225,6,1);
    LCD.FillRectangle(108,226,5,1);
    LCD.FillRectangle(109, 227, 4, 1);
    LCD.FillRectangle(110,228,4,1);
    LCD.FillRectangle(111,229,3,1);
    LCD.FillRectangle(112, 230,2,1);
    LCD.DrawPixel(113,231);

    //right button

    //set color to blue and draw rectangle
    LCD.SetDrawColor(LCD.Blue);
    LCD.FillRectangle(160, 210, 50, 25);
    
    // set color to white and draw right button arrow
    LCD.SetDrawColor(LCD.White);
    LCD.FillRectangle(165, 219, 34, 9);
    LCD.FillRectangle(199, 223, 9, 1);
    LCD.FillRectangle(199, 222, 8, 1);
    LCD.FillRectangle(199, 221, 7, 1);
    LCD.FillRectangle(199, 220, 6, 1);
    LCD.FillRectangle(199, 219, 5, 1);
    LCD.FillRectangle(199, 218, 4, 1);
    LCD.FillRectangle(199, 217, 3, 1);
    LCD.FillRectangle(199, 216, 2, 1);
    LCD.FillRectangle(199, 215, 1, 1);
    LCD.SetDrawColor(LCD.White);
    LCD.FillRectangle(199, 224, 8, 1);
    LCD.FillRectangle(199, 225, 7, 1);
    LCD.FillRectangle(199, 226, 6, 1);
    LCD.FillRectangle(199, 227, 5, 1);
    LCD.FillRectangle(199, 228, 4, 1);
    LCD.FillRectangle(199, 229, 3, 1);
    LCD.FillRectangle(199, 230, 2, 1);
    LCD.FillRectangle(199, 231, 1, 1);

}// end DrawButtons function


/*This function draws the ground plane of the game.  It has no input and no return since it is void. 
-Matthew Wong*/
void Environment::DrawGround(){
    //Set color to red and draw ground plane (double thickness)
    LCD.SetDrawColor(LCD.Red);
    LCD.DrawHorizontalLine(205, 0, 319);
    LCD.DrawHorizontalLine(204, 0, 319);
}//End DrawGround function



/*This function draws the buildings on the side of the screen in the game environemnt.  These buildings are
just art to fill up the space outside of the bounds of the user motion.  It has no inputs and no returns 
since it is a void function
-Janet Ann Purtell*/
void Environment::DrawBuildings(){
    //right building
    
    //draw main building
    LCD.SetDrawColor(DARKRED);
    LCD.FillRectangle(275, 86, 45, 118);

    //Draw roof
    LCD.SetDrawColor(GRAY);
    LCD.FillRectangle(270, 81, 50, 1);
    LCD.FillRectangle(271, 82, 49, 1);
    LCD.FillRectangle(272, 83, 48, 1);
    LCD.FillRectangle(273, 84, 47, 1);
    LCD.FillRectangle(274, 85, 46, 1);

    //Draw door & bush at bottom
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(292, 184, 15, 20);
    LCD.SetDrawColor(BLACK);
    LCD.FillRectangle(295, 191, 2, 2);
    LCD.SetDrawColor(FORESTGREEN);
    LCD.FillRectangle(282, 202, 4,2);
    LCD.FillRectangle(281, 201, 6, 1);
    LCD.FillRectangle(280, 200, 8, 1);
    LCD.FillRectangle(279, 199, 10, 1);
    LCD.FillRectangle(280, 198, 8, 1);
    LCD.FillRectangle(279, 197, 10, 1);
    LCD.FillRectangle(278, 196, 12, 1);
    LCD.FillRectangle(280, 195, 8, 1);
    LCD.FillRectangle(279, 194, 10, 1);
    LCD.FillRectangle(281, 193, 6, 10);
    LCD.FillRectangle(280, 192, 8, 1);
    LCD.FillRectangle(282, 190, 4, 2);
    LCD.FillRectangle(283, 189, 2, 1);

    //draw windows
    LCD.SetDrawColor(SKYBLUE);
    LCD.FillRectangle(280, 162, 8, 12);
    LCD.FillRectangle(280, 140, 8, 12);
    LCD.FillRectangle(280, 118, 8, 12);
    LCD.FillRectangle(280, 96, 8, 12);

    LCD.FillRectangle(294, 162, 8, 12);
    LCD.FillRectangle(294, 140, 8, 12);
    LCD.FillRectangle(294, 118, 8, 12);
    LCD.FillRectangle(294, 96, 8, 12);

    LCD.FillRectangle(308, 162, 8, 12);
    LCD.FillRectangle(308, 140, 8, 12);
    LCD.FillRectangle(308, 118, 8, 12);
    LCD.FillRectangle(308, 96, 8, 12);


    //left building
    
    //draw main building
    LCD.SetDrawColor(DARKRED);
    LCD.FillRectangle(0, 86, 45, 118);

    //draw roof
    LCD.SetDrawColor(GRAY);
    LCD.FillRectangle(0, 81, 50, 1);
    LCD.FillRectangle(0, 82, 49, 1);
    LCD.FillRectangle(0, 83, 48, 1);
    LCD.FillRectangle(0, 84, 47, 1);
    LCD.FillRectangle(0, 85, 46,1);

    //draw windows
    LCD.SetDrawColor(SKYBLUE);
    LCD.FillRectangle(4, 162, 8,12);
    LCD.FillRectangle(4, 140, 8, 12);
    LCD.FillRectangle(4, 118, 8, 12);
    LCD.FillRectangle(4, 96, 8, 12);

    LCD.FillRectangle(18, 162, 8,12);
    LCD.FillRectangle(18, 140, 8,12);
    LCD.FillRectangle(18, 118, 8,12);
    LCD.FillRectangle(18, 96, 8,12);

    LCD.FillRectangle(32, 162, 8,12);
    LCD.FillRectangle(32, 140, 8,12);
    LCD.FillRectangle(32, 118, 8,12);
    LCD.FillRectangle(32, 96, 8, 12);

    //draw door and bush at the bottom
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(17, 184, 15, 20);
    LCD.SetDrawColor(BLACK);
    LCD.FillRectangle(20, 191, 2, 2);
    LCD.SetDrawColor(FORESTGREEN);
    LCD.FillRectangle(7, 202, 4,2);
    LCD.FillRectangle(6, 201, 6, 1);
    LCD.FillRectangle(5, 200, 8, 1);
    LCD.FillRectangle(4, 199, 10, 1);
    LCD.FillRectangle(5, 198, 8, 1);
    LCD.FillRectangle(4, 197, 10, 1);
    LCD.FillRectangle(3, 196, 12, 1);
    LCD.FillRectangle(5, 195, 8, 1);
    LCD.FillRectangle(4, 194, 10, 1);
    LCD.FillRectangle(6, 193, 6, 10);
    LCD.FillRectangle(5, 192, 8, 1);
    LCD.FillRectangle(7, 190, 4, 2);
    LCD.FillRectangle(8, 189, 2, 1);


}//End drawbuildings function

/*This function draws the heart icon that reprents how many lives the user has left.  This function has no
inputs and is void so it returns nothing.  It access the variables x and y which are defined in the class
Environment as the starting position for drawing the heart icon.  This function only draws the icon, it 
does not display the actual counter of how many lives the user has left.  That is done in ano function
-Matthew Wong*/
void Environment::DrawLives(){
    
    //Set Draw color to scarlet
    LCD.SetDrawColor(SCARLET);
    //draw bottom pixel
    LCD.DrawPixel(x,y);
    //for loop to draw end of heart
    for(i = 0; i < 12; i++){
        x = x-1;
        y = y-1;
        length = length+2;
        LCD.FillRectangle(x, y, length, 1);
    }//end draw bottom of heart for loop
    
    //draw rest of heart
    LCD.FillRectangle(x, y-5, 25, 5);
    LCD.FillRectangle(x+1, y-6, 11, 1);
    LCD.FillRectangle(x+2, y-7, 9, 1);
    LCD.FillRectangle(x+3, y-8, 7, 1);
    LCD.FillRectangle(x+4, y-9, 5, 1);

    
    LCD.FillRectangle(x+12, y-6, 11, 1);
    LCD.FillRectangle(x+13, y-7, 9, 1);
    LCD.FillRectangle(x+14, y-8, 7, 1);
    LCD.FillRectangle(x+15, y-9, 5, 1);

    //reset these variables so the heart always prints in the same location
    x = 240;
    y = 232;
    length = 1;

    //draw a black rectangle next to the heart so the statistic is never drawn over top of something
    LCD.SetDrawColor(LCD.Black);
    LCD.FillRectangle(279, 212, 30, 20);

}//end draw lives

/*this function prints the word SCORE at the bottom of the screen.  It is inted that the score will
be dispalyed next to it yet this function does not diplay that statistic on the lable.  The function 
has no inputs and no return since it is void. 
-Matthew Wong*/

void Environment::DrawScore(){

    LCD.WriteAt("SCORE:", 5, 213);


}//end DrawScore

/* This function draws fire on top of each of the buildings to fit the plot.  It is passed the 
value of x at which the fire is to be drawn and has no return since it is void. 
-Matthew Wong*/

void Environment::DrawFire(int x){

    //define the y position at which the fire will be drawn
    int y = 80;
    //draw red pixels
    LCD.SetDrawColor(RED);
    LCD.FillRectangle(x, y, 10, 2);
    LCD.FillRectangle(x - 1, y - 1, 13, 2);
    LCD.FillRectangle(x - 2, y - 3, 14, 2);
    LCD.FillRectangle(x - 3, y - 4, 16, 2);
    LCD.FillRectangle(x - 2, y - 6, 13, 4);
    LCD.FillRectangle(x - 3, y - 10, 14, 2);
    LCD.FillRectangle(x - 4, y - 12, 12, 1);
    LCD.DrawPixel(x -3, y - 14);
    LCD.DrawPixel(x - 3, y - 15);
    LCD.DrawPixel(x - 4, y - 16);
    LCD.DrawPixel(x - 4, y - 17);
    LCD.DrawPixel(x - 4, y - 18);
    LCD.DrawPixel(x - 3, y - 19);
    LCD.DrawPixel(x - 2, y - 20);
    LCD.DrawPixel(x - 1, y - 21);
    LCD.DrawPixel(x, y - 20);
    LCD.DrawPixel(x, y - 19);
    LCD.DrawPixel(x - 1, y - 18);
    LCD.DrawPixel(x - 1, y - 17);
    LCD.DrawPixel(x, y - 17);
    LCD.DrawPixel(x, y - 16);
    LCD.DrawPixel(x + 1, y - 16);
    LCD.DrawPixel(x + 2, y - 16);
    LCD.FillRectangle(x + 2, y - 15, 1, 3);
    LCD.DrawPixel(x + 1, y - 18);
    LCD.DrawPixel(x + 2, y - 19);
    LCD.DrawPixel(x + 3, y - 18);
    LCD.DrawPixel(x + 3, y - 17);
    LCD.FillRectangle(x + 4, y - 17, 4, 3);
    LCD.FillRectangle(x + 6, y - 16, 3, 3);
    LCD.FillRectangle(x + 9, y - 16, 4, 3);
    LCD.FillRectangle(x + 10, y - 19, 3, 4);
    LCD.DrawPixel(x + 11, y - 21);
    LCD.DrawPixel(x + 12, y - 20);
    LCD.FillRectangle(x + 11, y - 19, 1, 3);    
    LCD.FillRectangle(x+12, y-6, 1, 4);
    LCD.FillRectangle(x, y - 15, 6, 13);
    LCD.DrawPixel(x + 15, y - 20);
    LCD.DrawPixel(x + 10, y - 18);
    LCD.DrawPixel(x - 5, y - 11);

    //draw yellow pixels
    LCD.SetDrawColor(YELLOW);
    LCD.FillRectangle(x, y-1, 10, 1);
    LCD.FillRectangle(x-1, y-2, 12, 1);
    LCD.FillRectangle(x-2, y-4, 14, 2);
    LCD.FillRectangle(x-2, y-6, 9, 2);
    LCD.DrawPixel(x+7, y-5);
    LCD.FillRectangle(x+10, y, 3, 3);
    LCD.FillRectangle(x - 1, y - 15, 2, 11);
    LCD.FillRectangle(x + 3, y - 16, 2, 8);
    LCD.FillRectangle(x + 7, y - 13, 3, 12);
   
} //End DrawFire function

/*  Thanks for reading our code :)
       All the best, -West Coast Gang
*/