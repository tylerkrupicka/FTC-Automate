void driveArcade(float x1, float y1, float x2, float y2){
	//function to scale y values to non-linear acceleration. computed in excel.
	int leftY = 0.0000141626*(y1)*(y1)*(y1) - 0.00025542*(y1)*(y1) + 0.581583*(y1) + 0.092436;
	int rightY = 0.0000141626*(y2)*(y2)*(y2) - 0.00025542*(y2)*(y2) + 0.581583*(y2) + 0.092436;

	//Deadzone////
	if(rightY > -15 && rightY < 15 && leftY > -15 && leftY < 15)
	{
		motor[FL] = 0;
		motor[ML] = 0;
		motor[BL] = 0;
		motor[FR] = 0;
		motor[MR] = 0;
		motor[BR] = 0;
	}
	else{
		//tank drive
		motor[FL] = leftY;
		motor[ML] = leftY;
		motor[BL] = leftY;
		motor[FR] = rightY;
		motor[MR] = rightY;
		motor[BR] = rightY;

	}
}
