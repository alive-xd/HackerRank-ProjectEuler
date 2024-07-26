import java.io.*;
import java.util.*;
import java.lang.*;
import java.util.Arrays;

public class Solution {

    //Constant alphabet array. Will be used to determine a letter score based on index.
    protected static final char[] ALPHABET_ENG = "abcdefghijklmnopqrstuvwxyz".toCharArray();

    //String array will temporarily hold names for sorting.
    //ArrayList will hold the sorted names.
    protected static String[] namesToBeSorted;
    protected static ArrayList < String > listOfNames;

    /**
     * Main method receives user string inputs (names of people).
     * It then calls method 'calculateNameScore' in order to get the score of each name.
     *
     * @param String[] args NULL
     **/
    public static void main(String[] args) {

        //scanner creation.
        Scanner scan = new Scanner(System.in);

        //integer value of amount of names to be added.
        int amountOfNames = scan.nextInt();

        //temporary names array will hold all names provided for sorting.
        namesToBeSorted = new String[amountOfNames];

        //names added to array.
        for (int index = 0; index < namesToBeSorted.length; index++) {

            //each name is added.
            String name = scan.next();
            namesToBeSorted[index] = name;
        }

        //names are sorted in alphabetical order and are transferred over to ArrayList.
        Arrays.sort(namesToBeSorted);
        listOfNames = new ArrayList < String > (Arrays.asList(namesToBeSorted));

        //integer for number of names to be scored.
        int queries = scan.nextInt();

        //loop runs until each name is scored.
        while (queries-- > 0) {

            //name is grabbed and scoring method is called.
            String nameToBeScored = scan.next();
            System.out.println(calculateNameScore(nameToBeScored));
        }
    }

    /**
     * Method calculates the score of a string.
     *
     * By using the index of the alphabet (1 throught 26), each letter of a given string
     * is indexed with the alphabet. Then the index of each letter in the alphabet is
     * added up and multiplied by the string location (index + 1) in the ArrayList.
     *
     * @param String givenName String to be scored.
     * @return int nameScore Score of the string.
     **/
    protected static int calculateNameScore(final String givenName) {

        //integer variable for the score of a given name.
        int nameScore = 0;

        //character array for each name and location in ArrayList.
        char[] nameScoringArray = givenName.toCharArray();
        int namePlace = listOfNames.indexOf(givenName) + 1;

        //loop runs until each letter is scored and added up.
        for (int index = 0; index < nameScoringArray.length; index++) {

            //each letter is scored.
            nameScore += findCharacterIndex(ALPHABET_ENG, Character.toLowerCase(nameScoringArray[index])) + 1;
        }

        //name score is multiplied with location in ArrayList and returned.
        return nameScore * namePlace;
    }

    /**
     * Method find the index of a character in an character array.
     *
     *
     * @param char[] array Character array to be searched.
     * @return char character The character to be searched for.
     **/
    protected static int findCharacterIndex(char[] array, char character) {

        //loop runs until index of the given character is found.
        for (int index = 0; index < array.length; index++)

            //character index returned if found.
            if (character == array[index]) {
                return index;
            }

        //if not found.
        return -1;
    }
}