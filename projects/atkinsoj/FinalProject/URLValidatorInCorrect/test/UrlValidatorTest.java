

import java.util.HashMap;
import java.util.HashSet;
import java.util.Random;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       setUpRandom(-1);
      
       // Perform a simple test to fail fast. 
       assertTrue("Simple test of example URL", urlValidator.isValid("http://www.google.com"));

       StringBuilder testUrlBuffer;
       StringPair stringPair;
       boolean expectedResult, result;
       String testUrl;
       int successCases = 0, failedCases = 0;
 
       
       for (int i = 0; i < 8000; i++) {

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
           System.out.println("About to test with: " + testUrl);  // DEBUG

           try { 
               result = urlValidator.isValid(testUrl);

               if ( assertBooleanCase(expectedResult + ": " + testUrl, expectedResult, result) ) {
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
       return new StringPair("www.example.com", true);
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
       StringBuffer buf = new StringBuffer();
       if (Math.random() <= .95) { 
           buf.append("/");
       }
       return new StringPair("/blah", true);
   }
   
   private StringPair generateRandomQuery() {
       return new StringPair("?search=example", true);
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
