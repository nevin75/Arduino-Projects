using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace RPG_Tests
{
    [TestClass]
    class CharacterTests
    {
        [TestMethod]
        public void CreateCharacter_WithDefaults_ShouldReturnAverage()
        {
            Character newCharacter = new Character();
            var expected = "somewhat fit";

            var result = newCharacter.fitnessLevel;

            Assert.AreEqual(expected, result);
        }
    }
}
