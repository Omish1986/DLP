import java.util.*;

public class FiniteAutomaton {
public static boolean isValid(int noOfSymbol ,String inputSymbols,int noOfState,int initialState,Set<Integer> acceptingStates,String inputString){
        boolean checkStringContainInputSymbol=false;
        Scanner scanner = new Scanner(System.in);

        for(int i=0;i<inputString.length();i++){
            for(int j=0;j<inputSymbols.length();j++){
                if(inputString.charAt(i)==inputSymbols.charAt(j)){
                             checkStringContainInputSymbol=true;
                             break;
                }
            }
            if(!checkStringContainInputSymbol){
                return false;
            }
            checkStringContainInputSymbol=false;
        }
        Map<Integer, Map<Character, Integer>> transitionTable = new HashMap<>();
        for(int i=0;i<noOfState;i++){
            transitionTable.put(i+1, new HashMap<>());
            for(int j=0;j<inputSymbols.length();j++){
                System.out.println("Enter next state if current state is "+(i+1)+" and input symbol is "+inputSymbols.charAt(j)+" : ");
                int tempState=scanner.nextInt();
                transitionTable.get(i+1).put(inputSymbols.charAt(j), tempState);
            }
        }


        int currentState = initialState;
        for (int i = 0; i < inputString.length(); i++) {
            char symbol = inputString.charAt(i);
            
            // Check if the current state has a transition for the given symbol
            if (transitionTable.containsKey(currentState) && 
                transitionTable.get(currentState).containsKey(symbol)) {
                currentState = transitionTable.get(currentState).get(symbol);
            } else {
                // If no valid transition exists, the string is invalid
                return false;
            }
        }

        // Check if the final state is one of the accepting states
        if (acceptingStates.contains(currentState)) {
            return true;
        } else {
            return false;
        }
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter number of input symbols: ");
        int noOfSymbol = scanner.nextInt();
        scanner.nextLine();
        System.out.println("Enter input symbols: ");
        String inputSymbols = scanner.nextLine();
        System.out.println("Enter number of states: ");
        int noOfState = scanner.nextInt();
        System.out.println("Enter initial state: ");
        int initialState = scanner.nextInt();
        System.out.println("Enter number of accepting states: ");
        int noOfAcceptingStates = scanner.nextInt();
        Set<Integer> acceptingStates = new HashSet<>();
        System.out.println("Enter accepting states: ");
        for (int i = 0; i < noOfAcceptingStates; i++) {
            acceptingStates.add(scanner.nextInt());
        }
        scanner.nextLine();
        System.out.println("Enter input inputString: ");
        final String inputString = scanner.nextLine();
        boolean b=isValid(noOfSymbol,inputSymbols,noOfState,initialState,acceptingStates,inputString);

        if(b){
            System.out.println("The input string is valid.");
        }
        else{
            System.out.println("The input string is invalid.");
        }
        
        scanner.close();
    }
}
