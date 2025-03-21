import java.util.*;
import java.io.*;

public class LexicalAnalyzer {
    private static final Set<String> keywords = new HashSet<>(Arrays.asList(
            "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
            "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
            "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
            "union", "unsigned", "void", "volatile", "while"));

    private static final Set<Character> operators = new HashSet<>(Arrays.asList(
            '+', '-', '*', '/', '%', '=', '<', '>', '!', '&', '|', '^', '~', '.'));

    private static final Set<String> compoundOperators = new HashSet<>(Arrays.asList(
            "++", "--", "+=", "-=", "*=", "/=", "%=",
            "==", "<=", ">=", "!=", "&&", "||", "<<", ">>"));

    private static final Set<Character> punctuation = new HashSet<>(Arrays.asList(
            ',', ';', '(', ')', '{', '}', '[', ']'));

    private static List<String> symbolTable = new ArrayList<>();
    private static List<String> lexicalErrors = new ArrayList<>();

    public static void analyzeFile(String fileName) {
        try {
            File file = new File(fileName);
            BufferedReader reader = new BufferedReader(new FileReader(file));
            StringBuilder sourceCode = new StringBuilder();
            String line;

            while ((line = reader.readLine()) != null) {
                sourceCode.append(line).append("\n");
            }
            reader.close();

            symbolTable.clear();
            lexicalErrors.clear();

            analyze(sourceCode.toString());

        } catch (FileNotFoundException e) {
            System.err.println("Error: File not found in the current directory");
            System.err.println("Make sure exists in the same directory as this program");
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }

    private static void analyze(String sourceCode) {
        String cleanCode = removeComments(sourceCode);
        List<Token> tokens = tokenize(cleanCode);

        System.out.println("TOKENS");
        System.out.println("------");
        for (Token token : tokens) {
            System.out.println(token.type + ": " + token.value);
        }

        System.out.println("\nSYMBOL TABLE ENTRIES");
        System.out.println("-------------------");
        for (int i = 0; i < symbolTable.size(); i++) {
            System.out.println((i + 1) + ") " + symbolTable.get(i));
        }

        if (!lexicalErrors.isEmpty()) {
            System.out.println("\nLEXICAL ERRORS");
            System.out.println("--------------");
            for (String error : lexicalErrors) {
                System.out.println(error);
            }
        }
    }

    private static String removeComments(String sourceCode) {
        StringBuilder result = new StringBuilder();
        char[] code = sourceCode.toCharArray();
        int i = 0;

        while (i < code.length) {
            if (i + 1 < code.length && code[i] == '/' && code[i + 1] == '/') {
                while (i < code.length && code[i] != '\n')
                    i++;
            } else if (i + 1 < code.length && code[i] == '/' && code[i + 1] == '*') {
                i += 2;
                while (i + 1 < code.length && !(code[i] == '*' && code[i + 1] == '/'))
                    i++;
                i += 2;
            } else {
                result.append(code[i]);
                i++;
            }
        }
        return result.toString();
    }

    private static List<Token> tokenize(String code) {
        List<Token> tokens = new ArrayList<>();
        char[] chars = code.toCharArray();
        int i = 0;

        while (i < chars.length) {
            char c = chars[i];

            if (Character.isWhitespace(c)) {
                i++;
                continue;
            }

            if (c == '"' || c == '\'') {
                StringBuilder string = new StringBuilder();
                char quote = c;
                string.append(quote);
                i++;
                while (i < chars.length && chars[i] != quote) {
                    string.append(chars[i]);
                    i++;
                }
                if (i < chars.length) {
                    string.append(chars[i]);
                    tokens.add(new Token("String", string.toString()));
                }
                i++;
                continue;
            }

            if (Character.isDigit(c)) {
                StringBuilder number = new StringBuilder();
                while (i < chars.length &&
                        (Character.isDigit(chars[i]) || chars[i] == '.' || Character.isLetter(chars[i]))) {
                    number.append(chars[i]);
                    i++;
                }
                String numStr = number.toString();

                boolean isValid = true;
                int decimalPoints = 0;
                for (char ch : numStr.toCharArray()) {
                    if (ch == '.') {
                        decimalPoints++;
                    } else if (!Character.isDigit(ch)) {
                        isValid = false;
                        break;
                    }
                }

                if (isValid && decimalPoints <= 1) {
                    tokens.add(new Token("Constant", numStr));
                } else {
                    lexicalErrors.add("Invalid numeric constant: " + numStr);
                }
                continue;
            }

            if (Character.isLetter(c) || c == '_') {
                StringBuilder identifier = new StringBuilder();
                while (i < chars.length && (Character.isLetterOrDigit(chars[i]) || chars[i] == '_')) {
                    identifier.append(chars[i]);
                    i++;
                }
                String word = identifier.toString();
                if (keywords.contains(word)) {
                    tokens.add(new Token("Keyword", word));
                } else {
                    tokens.add(new Token("Identifier", word));
                    if (!symbolTable.contains(word)) {
                        symbolTable.add(word);
                    }
                }
                continue;
            }

            if (operators.contains(c)) {
                StringBuilder operator = new StringBuilder();
                operator.append(c);

                if (i + 1 < chars.length) {
                    char nextChar = chars[i + 1];
                    String possibleCompound = operator.toString() + nextChar;
                    if (compoundOperators.contains(possibleCompound)) {
                        operator.append(nextChar);
                        i++;
                    }
                }

                tokens.add(new Token("Operator", operator.toString()));
                i++;
                continue;
            }

            if (punctuation.contains(c)) {
                tokens.add(new Token("Punctuation", String.valueOf(c)));
                i++;
                continue;
            }

            if (!Character.isWhitespace(c)) {
                lexicalErrors.add(c + " invalid lexeme");
            }
            i++;
        }

        return tokens;
    }

    private static class Token {
        String type;
        String value;

        Token(String type, String value) {
            this.type = type;
            this.value = value;
        }
    }

    public static void main(String[] args) {
        analyzeFile("testcase-3.c");
    }
}
