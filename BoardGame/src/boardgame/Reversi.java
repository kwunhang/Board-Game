/**
 * CSCI1130 Java Assignment 6 BoardGame Reversi
 * Aim: Practise subclassing, method overriding
 *      Learn from other subclass examples
 * 
 * I declare that the assignment here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   http://www.cuhk.edu.hk/policy/academichonesty
 * Faculty of Engineering Guidelines to Academic Honesty:
 *   https://www.erg.cuhk.edu.hk/erg/AcademicHonesty
 *
 * Student Name: Lau Kwun Hang
 * Student ID  : 1155158471
 * Date        : 11/12/2021
 */

package boardgame;

import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JOptionPane;

/**
 * Reversi is a TurnBasedGame
 */
public class Reversi extends TurnBasedGame {
    
    public static final String BLANK = " ";
    String winner;


    /*** TO-DO: STUDENT'S WORK HERE ***/
    
    boolean [][] triggeredCheck;        //set variable to check the button have been triggered or not
    
    public Reversi()
    {
        super(8,8,"BLACK","WHITE");
        this.setTitle("Reversi");
    }
    
    protected boolean isFriend(int x, int y)
    {
        return pieces[x][y].getText().equals(currentPlayer);
    }
    
    protected boolean isOpponent(int x, int y)
    {
        return pieces[x][y].getText().equals(getOpponent());
    }
    
    public boolean isValidMove(int x, int y)                //checking the is the triggeredbutton a valid move
    {
        if(triggeredCheck[x][y])
            return false;
        for(int deltaX = -1; deltaX <= 1;deltaX++){
            for(int deltaY = -1; deltaY <= 1; deltaY++){    // (deltaX,deltaY) be the 8 vectors of triggerButton to check,(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)
                if(deltaX == 0 && deltaY == 0) continue;    // except the vector of (0,0)
                //find opponent in surrounding
                int counter = 1;
                try{
                    while(isOpponent(x+deltaX*counter,y+deltaY*counter)){      //if the block is oppoenent,keep checking.What if the block is empty, the loop would end and try another vector
                        counter++;
                        if(isFriend(x+deltaX*counter,y+deltaY*counter))     //if meet friend at counter >= 2, it is a valid move
                            return true;
                    }
                        
                }
                catch(ArrayIndexOutOfBoundsException e)
                {}
            }
        }
        return false;   //all the vector is tried and no pieces would be fliped, so the move is invalid and return false
    }
    //*************************************************
    //following is inchanging 
    @Override
    protected void initGame()
    {
        triggeredCheck = new boolean[xCount][yCount];       //set the triggeredCheck
        for (int y = 0; y < yCount; y++)                    //initialize the gameboeard
            for (int x = 0; x < xCount; x++){
                pieces[x][y].setText(" ");
                triggeredCheck[x][y] = false;
            }
        pieces[3][4].setText("BLACK");                      //setting up the four starting pieces
        pieces[3][4].setBackground(Color.BLACK);
        pieces[4][3].setText("BLACK");
        pieces[4][3].setBackground(Color.BLACK);
        pieces[3][3].setText("WHITE");
        pieces[3][3].setBackground(Color.WHITE);
        pieces[4][4].setText("WHITE");
        pieces[4][4].setBackground(Color.WHITE);
        for(int x=3; x<=4; x++)
            for(int y=3; y<=4; y++)
                triggeredCheck[x][y] = true;        //assume the four starting button have been triggered
    }
    
    @Override
    protected void gameAction(JButton triggeredButton, int x, int y)
    {
        //check the validation of input
        if(!isValidMove(x, y)){
            addLineToOutput("Invalid move!");
            return;
        }
        
        //trigger the triggeredButton
        triggeredButton.setText(currentPlayer);
        triggeredButton.setBackground(currentPlayer.equals("BLACK")? Color.BLACK : Color.WHITE);
        triggeredCheck[x][y] = true;
        
        //flip the captured pieces with similar ways used in isValidMove
        for(int deltaX = -1; deltaX <= 1;deltaX++){
            for(int deltaY = -1; deltaY <= 1; deltaY++){    
                if(deltaX == 0 && deltaY == 0) continue;    
                //find opponent in surrounding
                int counter = 1;
                try{
                    while(isOpponent(x+deltaX*counter,y+deltaY*counter)){    
                        counter++;
                        if(isFriend(x+deltaX*counter,y+deltaY*counter)) {
                            //flip the captured pieces by valid array (deltaX, deltaY)
                            for(int i=1; i<counter; i++ ){
                                pieces[x+deltaX*i][y+deltaY*i].setText(currentPlayer);
                                pieces[x+deltaX*i][y+deltaY*i].setBackground(currentPlayer.equals("BLACK")? Color.BLACK : Color.WHITE);
                                triggeredCheck[x+deltaX*i][y+deltaY*i] = true;
                            }
                        } 
                            
                    }
                        
                }
                catch(ArrayIndexOutOfBoundsException e)
                {}
            }
        }
            
        addLineToOutput(currentPlayer + " piece at(" + x + ", " + y + ")");     //let players reviews the game

        checkEndGame(x, y);
        
        if (gameEnded)                  //when gameEnded is true, it means that there are two consective passed
        {                               //then here are two turn are passed and start the conclusion
            changeTurn();
            addLineToOutput("Pass!");
            changeTurn();
            addLineToOutput("Pass!");
            int noOfBlack = countPieces("BLACK");
            int noOfWhite = countPieces("WHITE");
            addLineToOutput("BLACK score:"+noOfBlack);          //following is reporting the result
            addLineToOutput("WHITE score:"+noOfWhite);
            if(noOfBlack>noOfWhite)
                winner= "BLACK";
            else if(noOfBlack<noOfWhite)
                winner="WHITE";
            if(noOfBlack==noOfWhite)
                addLineToOutput("Draw game!");
            else
                addLineToOutput("Winner is "+winner+"!");
            addLineToOutput("Game ended!");
            JOptionPane.showMessageDialog(null, "Game ended!");
        }
        else if(mustPass()){        //Normally it should not be happenned. However, if mustpass is true, the turn change to opponent and pass to current player again
            changeTurn();
            addLineToOutput("Pass!");
            changeTurn();
        }
        else                        //nothing special and the game goes on
            changeTurn();
    }
    
    protected boolean mustPass(){           //in the method,it lets the opponent be the cuurent player and use isValideMove() to check.It is checking the 'opponent' need to pass or not
        currentPlayer = getOpponent();      //assume now the current player is changed already
        for( int x = 0; x < 8; x++){
            for( int y = 0; y < 8; y++){
                if(isValidMove(x,y)){
                    currentPlayer = getOpponent();      //revert current player
                    return false;
                }
            }
        }
        currentPlayer = getOpponent();      //revert current player
        return true;
    }
    
    @Override
    protected boolean checkEndGame(int moveX, int moveY)        //if pass happen consecutive, the game would end
    {
        gameEnded = false;
        int consecPass = 0;
        String tempOfCurrentPlayer = currentPlayer;             //keep the data of current player
        while(mustPass() && consecPass<2){
            currentPlayer = getOpponent();
            consecPass++;                                       //let the oponent be current player and check is there any valid move due to real current 
        }
        currentPlayer = tempOfCurrentPlayer;                    //revert the cuurrent player
        if (consecPass==2)
            gameEnded = true;
        return gameEnded;
        
    }
    
    protected int countPieces(String player){       //counter the pieces of the input player
        int noOfPieces = 0;
        for(int x=0; x<xCount; x++){
            for(int y=0; y<yCount; y++){
                if (pieces[x][y].getText().equals(player))
                    noOfPieces++;
            }
        }
        return noOfPieces;
    }

    
    public static void main(String[] args)
    {
        Reversi reversi;
        reversi = new Reversi();
        
        // TO-DO: run other classes, one by one
        System.out.println("You are running class Reversi");
        
        // TO-DO: study comment and code in other given classes
        
        // TO-DO: uncomment these two lines when your work is ready
        reversi.setLocation(400, 20);
        reversi.verbose = false;

        // the game has started and GUI thread will take over here
    }
}
