
int getRouteChoice() {
  int currMenuPosition = -1;
  int finalMenuChoice = -1;
  nNxtButtonTask  = -2;

  nxtDisplayCenteredBigTextLine(1,"RouteMenu");
	nxtDisplayCenteredTextLine(3,"Use arrow keys");
	nxtDisplayCenteredTextLine(4,"to choose an");
	nxtDisplayCenteredTextLine(5,"automomous");
	nxtDisplayCenteredTextLine(6,"routine. Press");
	nxtDisplayCenteredTextLine(7,"orange button");
	nxtDisplayCenteredTextLine(8,"to select.");

	while (true)
	{
		TButtons nBtn;

	  while (true) // wait for button press
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn != -1)
	  	  break;
	  }

	  switch (nBtn)
	  {
	  	case kLeftButton:
	  	  currMenuPosition -=1;
	  	  if (currMenuPosition < 0) {
	  	    currMenuPosition = ARRAYSIZE(autoRoutines) -1;
	  	  }
	  	  break;
			case kRightButton:
			  currMenuPosition +=1;
	  	  if (currMenuPosition == ARRAYSIZE(autoRoutines)) {
	  	    currMenuPosition = 0;
	  	  }
	  	  break;
			case kEnterButton:
			  finalMenuChoice = currMenuPosition;
			  break;
			case kExitButton:	   			break;
			default:                  break;
		}
		PlaySoundFile("! Click.rso");

	  while (true) // wait for button release
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn == -1)
	  	  break;
	  }
	  if (finalMenuChoice > -1) {
	    return finalMenuChoice;
	  }
	  eraseDisplay();
	  int numProgs = ARRAYSIZE(autoRoutines);
	  int currProg = currMenuPosition + 1;
	  nxtDisplayCenteredTextLine(1,"%s", autoRoutines[currMenuPosition]);
	  nxtDisplayCenteredTextLine(5, "Choice %d of %d",currProg, numProgs);
  }
}
// ////////////////////////////////////////////////////////////////////////////////


//Delay Menu
int getDelayChoice() {
  int currMenuPosition = -1;
  int finalMenuChoice = -1;
  nNxtButtonTask  = -2;

  nxtDisplayCenteredBigTextLine(1,"Delay Menu");
	nxtDisplayCenteredTextLine(3,"Use arrow keys");
	nxtDisplayCenteredTextLine(4,"to choose an");
	nxtDisplayCenteredTextLine(5,"automomous");
	nxtDisplayCenteredTextLine(6,"routine. Press");
	nxtDisplayCenteredTextLine(7,"orange button");
	nxtDisplayCenteredTextLine(8,"to select.");

	while (true)
	{
		TButtons nBtn;

	  while (true) // wait for button press
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn != -1)
	  	  break;
	  }

	  switch (nBtn)
	  {
	  	case kLeftButton:
	  	  currMenuPosition -=1;
	  	  if (currMenuPosition < 0) {
	  	    currMenuPosition = ARRAYSIZE(delayTimes) -1;
	  	  }
	  	  break;
			case kRightButton:
			  currMenuPosition +=1;
	  	  if (currMenuPosition == ARRAYSIZE(delayTimes)) {
	  	    currMenuPosition = 0;
	  	  }
	  	  break;
			case kEnterButton:
			  finalMenuChoice = currMenuPosition;
			  break;
			case kExitButton:	   			break;
			default:                  break;
		}
		PlaySoundFile("! Click.rso");

	  while (true) // wait for button release
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn == -1)
	  	  break;
	  }
	  if (finalMenuChoice > -1) {
	    return finalMenuChoice;
	  }
	  eraseDisplay();
	  int numProgs = ARRAYSIZE(delayTimes);
	  int currProg = currMenuPosition + 1;
	  nxtDisplayCenteredTextLine(1,"%s", delayTimes[currMenuPosition]);
	  nxtDisplayCenteredTextLine(5, "Choice %d of %d",currProg, numProgs);
  }
}
