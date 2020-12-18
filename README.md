# kcnGame

Game engine: Unreal Engine 4.25.4  

Game theme: FPS multiplayer

Game name: Spellshooter

# Group Members:     
    Vegard Opktivtne Årnes             vegardoa         vegardoa@stud.ntnu.no     GuthubID: VitriolicTurtle        GitLabID: AlphaBoi  
	Andreas Blakli                     andrbl           andrbl@stud.ntnu.no       GithubID: TrustworthyBlake       GitlabID: andrbl  
	Theo Camille Gascogne              theocg           theocg@stud.ntnu.no       GithubID: iaminadequate          GitlabID: iaminadequate  
  
  
# See the gameprog.md file for Project report and videos.  

# How to run:
 
It is important to note that the server must be manually restarded when the game mode finishes i.e. when a player wins the game mode.  
Executeable files for game and server provided in google drive.  
Game: https://drive.google.com/file/d/1l8zfD6XNvAMluZA1Z6ADgM3W0rV2tlsy/view?usp=sharing  
Server: https://drive.google.com/file/d/1uTCwMoHf7vcm8HzHuOw5mwY-15sYNFFu/view?usp=sharing  

We highly recommend making a shortcut for the server executable and add -log to the end of the path in the properties section of the shortcut, this makes it easier to close the server and see debug messages.  
  
**How to: Compile the game yourself**  
It's recomended that you just download the executables with the provided links above, but if you want to do it yourself this is how.  
Download and install Unreal Engine 4.25.4. from Unreals GitHub page, package and compile and build the engine, see documentation for this here: https://docs.unrealengine.com/en-US/ProgrammingAndScripting/ProgrammingWithCPP/DownloadingSourceCode/index.html  
git clone the repo  
Open Unreal engine from Visal Studio and in recent project choose browse and navigate to spellshooter.uproject  
When unreal ask you to build the project press yes.   
Then follow Unreal's documentation which is provided here: https://docs.unrealengine.com/en-US/Engine/Basics/Projects/Packaging/index.html  
  
Setting up the dedicated server: https://docs.unrealengine.com/en-US/Gameplay/Networking/HowTo/DedicatedServers/index.html  
  
# Controls: 
W = Move player forward  
A = Move player to the left  
S = Move player backward  
D = Move player to the right  
Spacebar = Jump  

Mouse to control aim  
MouseLeftClick = Shoot  
  
P = Open pause menu  
F = Change between Alien and Human character  
B = Opens up buy menu  

# About the game
The game is set on the planet mars where humanity have invaded the Martians and a full-on war between the humans and Martians have developed. 
You the player spawns in on the map and chooses either to be an alien Martian or the invading human. 
Humans use normal guns for combat and the Martians use magical abilities.  
The game mode is Free For All, last man standing wins.

# Sources
