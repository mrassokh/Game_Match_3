
function recursiveMatch(timer1,timer2) {
    logic.reType();
    if (!logic.checkMatches()){
       logic.addStepNumber();
    } else {
       timer1.restart();
       timer2.restart();
    }
    if (logic.gameOver()){
       resultWindow.setX(mainWindow.x + mainWindow.width / 2 -  resultWindow.width / 2)
       resultWindow.setY(mainWindow.y + mainWindow.height / 2 -  resultWindow.height / 2)
       resultWindow.show();
    }
}


function clickProccesing(timer,timer1,timer2, index){
    if (!logic.getClicked()){
        logic.setStartIndex(index);
        logic.setClicked(true);
    } else {
        var endIndex = index;
        logic.setEndIndex(index);
        var startIndex = logic.getStartIndex();
        logic.setClicked(false);

         if (logic.checkMove(startIndex, endIndex)){
            logic.swapElements(startIndex, endIndex);
             if (!logic.checkMatches()){
                timer.restart();
             }  else    {
                timer1.restart();
                timer2.restart();
             }
         }
    }
}
