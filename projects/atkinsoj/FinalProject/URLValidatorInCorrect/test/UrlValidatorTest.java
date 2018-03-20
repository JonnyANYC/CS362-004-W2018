import java.util.Random;
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   /************ Manual testing **************/

   
   public void testManualTest()
   {     

    UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);  

    System.out.println("Starting Manual Test");

    //testing URLs that should be valid

        assertTrue(urlValidator.isValid("http://www.google.com"));
        assertTrue(urlValidator.isValid("http://www.yahoo.com"));
        assertTrue(urlValidator.isValid("http://8.8.8.8")); //correct IP range 
        assertTrue(urlValidator.isValid("http://www.google.au"));
        assertTrue(urlValidator.isValid("https://www.google.com:80")); //correct port
        assertTrue(urlValidator.isValid("https://www.google.com/awesome")); //correct path
        assertTrue(urlValidator.isValid("https://www.google.com/$156")); //correct path
        assertTrue(urlValidator.isValid("ftp://www.google.com/?action=view")); //correct query
        assertTrue(urlValidator.isValid("ftp://www.google.com/?action=edit&mode=up"));

    //testing URLs that should be invalid 

        // assertFalse(urlValidator.isValid("http:/www.google.com")); //missing a slash
        assertFalse(urlValidator.isValid("http://256.256.300.300")); //incorrect IP range
        assertFalse(urlValidator.isValid("http://8.8.8")); //incorrect IP format
        assertFalse(urlValidator.isValid("http://8.8.8.8.8")); //incorrect IP format
        assertFalse(urlValidator.isValid("http://.www.google.com")); //there's a "." right after the http://
        assertFalse(urlValidator.isValid("http://google")); //no .BLANK after "google"
        assertFalse(urlValidator.isValid("http://www.google.com:-20")); //invalid port number
        assertFalse(urlValidator.isValid("https://www.google.com:80q")); //invalid port number
        assertFalse(urlValidator.isValid("https://www.google.com/ ..")); //invalid path
        assertFalse(urlValidator.isValid("browser://www.google.com"));
        assertFalse(urlValidator.isValid("blah:/:::/www.google.com/ .."));

       
   }
   
   
   /********** Partition testing *************/
      
   
   public void testYourFirstPartition()
   {
      // Test paths
      UrlValidator UrlValidatorPartition = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/t123"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/$23"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/..")); // /.. invalid
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1/"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1/file"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/test1/...../"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/test1/../"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/~username"));
   }
   
   public void testYourSecondPartition(){
      // Test scheme
      UrlValidator UrlValidatorPartition = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      assertTrue(UrlValidatorPartition.isValid("http://www.google.com"));
      assertTrue(UrlValidatorPartition.isValid("ftp://www.google.com"));
      assertTrue(UrlValidatorPartition.isValid("h3t://www.google.com"));
      assertFalse(UrlValidatorPartition.isValid("3ht://www.google.com"));
      assertFalse(UrlValidatorPartition.isValid("http:/www.google.com"));
      assertFalse(UrlValidatorPartition.isValid("http:www.google.com"));
      assertFalse(UrlValidatorPartition.isValid("http/www.google.com"));
      assertFalse(UrlValidatorPartition.isValid("://www.google.com"));
      assertTrue(UrlValidatorPartition.isValid("www.google.com"));
   }

   public void testYourThirdPartition(){
      // Test ports
      UrlValidator UrlValidatorPartition = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      assertTrue(UrlValidatorPartition.isValid("http://www.google.com:80"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com:65535"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com:65536"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com:0"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com:-1"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com:65a"));
   }

   public void testYourFourthPartition(){
      // Test path options
      UrlValidator UrlValidatorPartition = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/t123"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/$23"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/.."));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/../"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1/"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/#"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1/file"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/t123/file"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/$23/file"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/../file"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/..//file"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1//file"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/#/file"));
   }

   public void testYourFifthPartition(){
      // Test query
      UrlValidator UrlValidatorPartition = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1?action=view"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1?action=edit&mode=up"));
      assertTrue(UrlValidatorPartition.isValid("http://www.google.com/test1"));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/test1?action=="));
      assertFalse(UrlValidatorPartition.isValid("http://www.google.com/test1?+"));
   }

   public void testYourSixthPartition(){
      // Test authority
      UrlValidator UrlValidatorPartition = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      assertTrue(UrlValidatorPartition.isValid("http://www.google.com"));
      assertTrue(UrlValidatorPartition.isValid("http://go.com"));
      assertFalse(UrlValidatorPartition.isValid("http://go,com"));
      assertTrue(UrlValidatorPartition.isValid("http://0.0.0.0"));
      assertTrue(UrlValidatorPartition.isValid("http://255.255.255.255"));
      assertFalse(UrlValidatorPartition.isValid("http://255.255.255.256"));
      assertFalse(UrlValidatorPartition.isValid("http://256.256.256.256"));
      assertFalse(UrlValidatorPartition.isValid("http://255.255.-1.256"));
      assertTrue(UrlValidatorPartition.isValid("http://255.com"));
      assertFalse(UrlValidatorPartition.isValid("http://1.2.3.4.5"));
      assertFalse(UrlValidatorPartition.isValid("http://1.2.3.4."));
      assertFalse(UrlValidatorPartition.isValid("http://"));
      assertFalse(UrlValidatorPartition.isValid("http://aaa"));
      assertFalse(UrlValidatorPartition.isValid("http://aaa."));
      assertFalse(UrlValidatorPartition.isValid("http://.aaa"));
      assertFalse(UrlValidatorPartition.isValid("http://go.1aa"));
      assertFalse(UrlValidatorPartition.isValid("http://.1.2.3.4"));
      assertFalse(UrlValidatorPartition.isValid("http://go.a"));
      assertFalse(UrlValidatorPartition.isValid("http://go.a1a"));
      assertFalse(UrlValidatorPartition.isValid("http://1.2.3"));

   }

   
   /*********** Programmatic testing ***********/
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       setUpRandom(-1);

       // Perform a simple test to fail fast. 
       assertTrue("Simple test of example URL", urlValidator.isValid("http://www.google.com"));
       //assertTrue("1", urlValidator.isValid("http://www.example.com/~4sKy?uC^E``Wx"));
              
       StringBuilder testUrlBuffer;
       StringPair stringPair;
       boolean expectedResult, result;
       String testUrl;
       int successCases = 0, failedCases = 0;
 
       
       for (int i = 0; i < 1000000; i++) {

           testUrlBuffer = new StringBuilder();
           expectedResult = true;
           
           stringPair = generateRandomScheme();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;
           
           stringPair = generateRandomHostname();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;

           stringPair = generateRandomPort();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;

           stringPair = generateRandomPath();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;

           stringPair = generateRandomQuery();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;
           
           testUrl = testUrlBuffer.toString();

           try { 
               result = urlValidator.isValid(testUrl);

               if ( assertBooleanCase(testUrl + " is " + expectedResult + " valid", expectedResult, result) ) {
                   successCases++;
               } else {
                   failedCases++;
               }
           } catch (Exception e) {
               failedCases++;
               System.out.println("FAIL: Exception: " + e.toString());
           } catch (Error e) {
               failedCases++;
               System.out.println("FAIL: Error: " + e.toString());
           }
       }
       
       System.out.println("RESULTS: " + failedCases + " failed of " + 
         (failedCases + successCases) + " total.");
       assertEquals("No failed cases", 0, failedCases);
   }
   
   private boolean assertBooleanCase(String message, boolean expected, boolean actual) {
       if (expected != actual) { 
           System.out.println("FAIL: " + message);
           return false;
       }
       
       return true;
   }

   private Random _random;

   private void setUpRandom(long seed) {
       
       _random = new java.util.Random();
       
       if (seed == -1) {
           seed = _random.nextLong();
       }
       
       _random.setSeed(seed);
       System.out.println("Seed set to: " + seed);
   }
   
   private StringPair generateRandomScheme() {

       int whichScheme = _random.nextInt(1000);
       switch (whichScheme) {
       case 0:
           // Generate a scheme of 6 characters of printable ASCII, code points 32 (incl.) to 127 (excl.)
           StringBuffer randomScheme = new StringBuffer(7);
           for (int i = 0; i < 6; i++) {
               randomScheme.appendCodePoint(_random.nextInt(95) + 32);
           }
           boolean valid = false;
           String randomSchemeString = randomScheme.toString();
           if (randomSchemeString == "http://" 
               || randomSchemeString == "https://" 
               || randomSchemeString == "ftp://"
               || randomSchemeString == "gopher://") {
               valid = true;
           }
           return new StringPair(randomScheme.toString(), valid);
       case 1: 
           return new StringPair("https://", true);
       case 2:
           return new StringPair("ftp://", true);
       case 3: 
           return new StringPair("gopher://", true);
       default:
           return new StringPair("http://", true);
       }
   }

   private StringPair generateRandomHostname() {
       
       StringBuffer host = new StringBuffer();
       boolean valid = true;
       
       // Test with random ASCII characters 1/20 of the time, and with letters and numbers the rest of the time.
       int typeOfHost = _random.nextInt(20);
       
       switch (typeOfHost) {
       case 0:
                     
           // Generate a host name of random printable ASCII characters.

           int numRandomHostChars = _random.nextInt(12);
           for (int i = 0; i < numRandomHostChars ; i++) {

               int nextChar = randomPrintableAscii();
               
               // Anything other than letters and numbers is invalid.
               if (nextChar < 46
                       || nextChar == 47
                       || (nextChar >= 58 && nextChar <= 64)
                       || (nextChar >= 91 && nextChar <= 96)
                       || nextChar > 123) {
                   valid = false;
               }
               
               host.appendCodePoint(nextChar);
           }
           return new StringPair(host.toString(), valid); 
           
       default:

           // Generate a host name of just characters and dots
           
           int numHostChars = _random.nextInt(12);

           for (int j = 0; j < numHostChars; j++) {

               int nextChar = randomPrintableAscii();
               
               // Anything other than letters and numbers is invalid.
               if (nextChar < 46
                       || nextChar == 47
                       || (nextChar >= 58 && nextChar <= 64)
                       || (nextChar >= 91 && nextChar <= 96)
                       || nextChar > 123) {
                   continue;
               }
               
               host.appendCodePoint(nextChar);
           }
           
           String hostname = host.toString();
           
           if (hostname.startsWith(".") || hostname.endsWith("."))  valid = false;
           if (hostname.length() == 0)  valid = false;

           return new StringPair(hostname, valid); 

       }
   }
   
   private StringPair generateRandomPort() {

       String port = "";
       boolean valid = true;
       
       if (_random.nextInt(1000) == 0 ) {
           port = ":" + Math.pow(2,16) + _random.nextInt(1000);
           valid = false;
       }
       
       if (_random.nextInt(10) > 7) {
           port = ":" + _random.nextInt( (int)Math.pow(2,16) );
           if (port == ":0") {
               valid = false;
           }
       }
       
       return new StringPair(port, valid);
   }
   
   private StringPair generateRandomPath() {

       // Always start the path with a slash. We could test a path w/o a slash, 
       // but then it could be construed as a very long hostname, which is a 
       // valid structure.
       StringBuffer path = new StringBuffer("/");
       boolean valid = true;

       // Generate a path of random printable ASCII characters.
       int numCharacters = 1;
       int numPathChars = _random.nextInt(20);
       for (int i = 0; i < numPathChars; i++) {

           int nextChar = randomPrintableAscii();
           
           // Skip any question marks here. We'll test multiples in the query.
           if (nextChar == 63) {
               continue;
           }
           
           // Also skip percent signs; we'll test them momentarily.
           if (nextChar == 37) {
               continue;           
           }

           // Also skip hash marks, since they make the rest of the URL irrelevant
           if (nextChar == 35) {
               continue;
           }
           
           if (nextChar == 32)  valid = false; // space
           if (nextChar == 34)  valid = false; // double quote
           if (nextChar == 60 || nextChar == 62)  valid = false; // angle brackets 
           if (nextChar >= 91 && nextChar <= 94)  valid = false; // square brackets, backslash, caret
           if (nextChar == 96)  valid = false; // backtick
           if (nextChar >= 123 && nextChar <= 125)  valid = false; // curly brackets, pipe

           path.appendCodePoint(nextChar);
           numCharacters++;
           
       }

       if (_random.nextInt(5) == 0) {
           int numEntities = _random.nextInt(2) + 1;
           int position = 0;

            // Once every 5 cases, Add 1-2 valid and/or invalid URL escape entities.
               for (int i = 0; i < numEntities && position < numCharacters - 2; i++) { 
                   position += _random.nextInt(numCharacters - position);
                   path.insert(position, '%'); 
                   String randomByte = Integer.toHexString(_random.nextInt(256));

                   if (randomByte.length() == 1) { 
                       path.insert(position+1, "0" + randomByte);
                   } else {
                       path.insert(position+1, randomByte);
                   }

                   numCharacters += 3;
                   position += 3;
               }
       }

       return new StringPair(path.toString(), valid);
   }



   private StringPair generateRandomQuery() {

       StringBuffer query = new StringBuffer("?");
       boolean valid = true;

       // Generate a query of random printable ASCII characters.
       int numCharacters = _random.nextInt(20);
       for (int i = 0; i < numCharacters; i++) {

           int nextChar = randomPrintableAscii();

           // Skip hash marks, since they make the rest of the URL irrelevant
           if (nextChar == 35)  continue;

           if (nextChar == 32)  valid = false; // space
           // if (nextChar == 63)  valid = false;  // Question mark
           // if (nextChar >= 91 && nextChar <= 94)  valid = false; // square brackets, backslash, caret

           query.appendCodePoint(nextChar);
       }

       return new StringPair(query.toString(), valid);
   }

   private int randomPrintableAscii() {
       int randomCodePoint = _random.nextInt(95) + 32;
       return randomCodePoint;
   }

   // Adapted from ResultPair in the original UrlValidatorTest.
   private class StringPair {
       public String elem;
       public boolean valid;

       public StringPair(String elem, boolean valid) {
            this.elem = elem;
            this.valid = valid;
       }
   }
}
