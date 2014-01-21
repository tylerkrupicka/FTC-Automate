void driveArcade(float x1, float y1, float x2, float y2){

   int leftY = 0.0000141626*(y1)*(y1)*(y1) - 0.00025542*(y1)*(y1) + 0.581583*(y1) + 0.092436;

   //Deadzone////

   if(x1 > -15 && x1 < 15 && leftY > -15 && leftY < 15)
    	{
      	motor[FL] = 0;
      	motor[ML] = 0;
      	motor[BL] = 0;
      	motor[FR] = 0;
      	motor[MR] = 0;
      	motor[BR] = 0;
    	}


   //Single Joystick Drive//

   if(x1 > 60 || x1 < -60){

		   if(x1 > 60){
		        motor[FL] = 75;
		      	motor[ML] = 75;
		      	motor[BL] = 75;
		      	motor[FR] = -75;
		      	motor[MR] = -75;
		      	motor[BR] = -75;
		   }
		   if(x1 < -60){
		        motor[FL] = -75;
		      	motor[ML] = -75;
		      	motor[BL] = -75;
		      	motor[FR] = 75;
		      	motor[MR] = 75;
		      	motor[BR] = 75;
		   }
   }
   else{
            motor[FL] = leftY;
		      	motor[ML] = leftY;
		      	motor[BL] = leftY;
		      	motor[FR] = leftY;
		      	motor[MR] = leftY;
		      	motor[BR] = leftY;
   }

}
