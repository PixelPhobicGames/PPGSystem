
**PPG System v.1.1.0 *- Release Notes***
----
Description 

What is **PPG System**?
--
 - **PPG System** is a Standalone **Parasite Script** Virtual Machine 
 -  Its a Container to Run the **Parasite Scripting Language** Created By **PixelPhobicGames**.
 - Parasite Script is a Lightweight and Simple High Level Programming Language used in Most  of the Game Engines Created by PixelPhobicGames.
 - **PPG System** runs a Version of Parasite That is made with the **Intention to Create Video Games**
 - Parasite is a Mix of the BASIC Language and Assembly 
---
Limitations of PPG System / Specifications
---
 - Parasite is a Very Simple Language so there are some Limits to what it can do 
 - These Consist of 
 - A Resolution of 320x240 
 - 30 FPS
 - 16384 Variable Limit 
 - 16384 Jump Point Limit 
 -  No Script File Size Limit 
 - All Programs Must Be in a Single file 
 - No Audio, Yet
 - 10 Colours
 
---
**Parasite Script Instructions / Cheat Sheet** 
---
	 Guide - 
	 
		 [] = Integer Number 
		 '' = String
		 {} = Varible 
		 || = Label Name
		 ^ = Sprite Pointer
		  # = Description
		 ** = Array Pointer
	 
	 Opcodes
	 ______________________________________________________________
	 stop   # Kills the Program
	 
	 jump []  # Will Set the Program Counter to Certain Line Number
	 jumpl ||  # Will Set Program Counter to Label Address
	 
	 Example:
		 jump 18  # Goes to Line 18
		 jumpl Main # Goes to Label "Main"
		 
	 addv { Destination } {}  # Adds two Varibles 
	 add { Destination } []  # Adds Integer to Varible
	 
	 Example :
		 addv MyVarible1 MyVarible2  # MyVarible1 = MyVarible1 + MyVarible2
		 add MyVarible1 18   # MyVarible1 = MyVarible1 + 18
		 
	 subv { Destination } {}  # Subtracts two Varibles 
	 sub { Destination } []  # Subtracts Integer from Varible
	 
	 Example :
		 subv MyVarible1 MyVarible2  # MyVarible1 = MyVarible1 - MyVarible2
		 sub MyVarible1 18   # MyVarible1 = MyVarible1 - 18
		 
	 mulv { Destination } {}  # Multiplies two Varibles 
	 mul { Destination } []  # Multiplies Varible by Integer

	 Example :
		 mulv MyVarible1 MyVarible2  # MyVarible1 = MyVarible1 * MyVarible2
		 mul MyVarible1 18   # MyVarible1 = MyVarible1 * 18
	 
	 divv { Destination } {}  # Divides two Varibles 
	 div { Destination } []  # Divides Varible by Integer
	 
	 Example :
		 divv MyVarible1 MyVarible2  # MyVarible1 = MyVarible1 / MyVarible2
		 div MyVarible1 18   # MyVarible1 = MyVarible1 / 18
	 
	 set { Destination }  '' or []  # Sets Varible to a Int or Str Value
	 setv { Destination }  {}  # Sets Varible Value to Another Varibles Value

	 Example :
		 set MyVarible1 18  # MyVarible1 = 18
		 set MyVarible1 'Hello World'  # MyVarible1 = 'Hello World'
		 setv MyVarible1 MyVarible2  # MyVarible1 = MyVarible2
	 
	 settextsize []  # Sets Text Size
	 
	 Example :
		 settextsize 20

     cmpvv {} {}  # Compares Two Varibles
     cmpvi {} []  # Compares Varible to Int
	 
	 Example :
		 cmpvv MyVarible1 MyVarible2 
		 cmpvi MyVarible1 18
	
	 jifne ||  # Jump to Label if cmp was Not Equal
	 jife ||  # Jump to Label if cmp was Equal 
	 jifg ||  # Jump to Label if cmp was Greater
	 jifl ||  # Jump to Label if cmp was Lesser
	
	 Example :
		 cmpvi MyVarible 22  # Get Result
		 jifne MyLabel1 # if Equal go to MyLabel1
		 jife MyLabel2 # if Not Equal go to MyLabel2
		 jifg MyLabel3 # if Greater go to MyLabel3
		 jifl MyLabel4 # if Lesser go to MyLabel4

	  wipe  # Clears Logic Flags 
	  ret   # Returns from Jump 
	  
	  pullinp {}  # Pulls Input Into Varible 
	  
	  # Key Maps
	  # Up - 1 , Right - 2 , Down - 3 , Left - 4 , Space - 5
	  # A - 6 , S - 7
	  
	  
	  Example :
		  pullinp MyVarible  # MyVarible = KeyInput

	  drawspr ^ {X} {Y} {Scale} {Original Size in Pixels} # Draws Sprite
	  
	  Example :
		  spr ExampleSprite '+++++00+++++++++++++0770++00+++++000076600770+++07706066667660++06666666606660++066600666666660++06676000066660++07666666666660+067776666607666006777666666006600666776666666660+966776666666660++9966669966669+++++9999++9999+++++++++++++++++++++++++++++++++++'
		  var SpriteX 70
		  var SpriteY 50
		  var SpriteScale 4
		  var SpriteSize 16
		  
		  :Main
		      drawspr ExampleSprite SpriteX SpriteY SpriteScale SpriteSize
		      jumpl Main
		      
	  arrset ** {Index Varible} or [] {Number Varible} or []  # Sets Data in an Array to a Number or Varible 
	  arrload ** {Index Varible} or [] {OutPut Varible}  # Reads Number From a An Array Into a Varible
	  arrwipe ** []  # Fills Array with a Number

	  Example :
		  arr MyArray 0  
		  # The '0' is the Fill Character
		  
		  var Index 0
		  
		  arrset MyArray 1 1  # MyArray[1] = 0
		  arrset MyArray Index 1  # MyArray[0] = 0 or MyArray[Index] = 0
		  
		  var ArrayData 0
		  arrload MyArray 1 ArrayData  # ArrayData = MyArray[1]
		  arrload MyArray Index ArrayData  # ArrayData = MyArray[0] or MyArray[Index}
		  arrwipe MyArray 0
	   
	   clear  # Clears Screen
	   delay []  # Delays Number of Frames
	   pspeed []  # Sets Speed of PPGSystem Processor , or Instructions Per Frame 
		  
		  
		  
___
**Data Types**
___
	 var {Name} [] or '' # General Varible , Can Hold Text or Integer
	 spr {Name} ''  # Sprite Pointer , Used for Holding Sprite Data
	 arr {Name} [Fill Number]  # Simple Array, Only Numbers 
	 
	 Example :
		 var MyVarible1 'Hello World'
		 var MyVarible2 25
		 arr MyArray 0
		 spr ExampleSprite '+++++00+++++++++++++0770++00+++++000076600770+++07706066667660++06666666606660++066600666666660++06676000066660++07666666666660+067776666607666006777666666006600666776666666660+966776666666660++9966669966669+++++9999++9999+++++++++++++++++++++++++++++++++++'

	 Labels
	 
	 How to Make a Label
	 
	 Example :
		 
		 :MyLabel  # Creates Label Called MyLabel
		 
			 ret
---
**Operating System Commands**
___

 - PPG System Will by default Load into a Simple OS
 - It Only has a Small Number off Commands
 - Commands 

	 END  # Kill Program
	 CLS  # Clear Screen
	 SEI  # Launch Sprite Editor
	 LOAD  # Load Program From "Apps/" Folder
	 RUN  # Run Program 
	 
	 Examples :
	 
			 CLS
			 LOAD TEST
			 RUN
* Note Do Not Add a .ps in The Operating System when Referring to a Program.
* You Can Open .ps Files with the PPGSystem.exe App and It Will Start an App Automatically.
		 
---

Thank You :)


		 
	 
		  

	 

		  

	 

