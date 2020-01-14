void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

You can use & (bitwise and) and << (left shift).

For example, (1 << 3) results in "00001000" in binary. So your code could look like:

char eightBits = 0;

//Set the 5th and 6th bits from the right to 1
eightBits &= (1 << 4);
eightBits &= (1 << 5);
//eightBits now looks like "00110000". 
Then just scale it up with an array of chars and figure out the appropriate byte to modify first.

For more efficiency, you could define a list of bitfields in advance and put them in an array:

#define BIT8 0x01
#define BIT7 0x02
#define BIT6 0x04
#define BIT5 0x08
#define BIT4 0x10
#define BIT3 0x20
#define BIT2 0x40
#define BIT1 0x80

char bits[8] = {BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, BIT8};
Then you avoid the overhead of the bit shifting and you can index your bits, turning the previous code into:

eightBits &= (bits[3] & bits[4]);
Alternatively, if you can use C++, you could just use an std::vector<bool> which is internally defined as a vector of bits, complete with direct indexing.}
