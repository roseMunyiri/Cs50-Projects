// Select all buttons with the class ".btn"
const choiceButtons = document.querySelectorAll(".btn");

// Select the correct answer button
const correctChoice = document.querySelector("#btn5");

// Add a click event listener to each button
choiceButtons.forEach((button) => {
  button.addEventListener("click", function () {
    // Reset all buttons to initial state
    choiceButtons.forEach((btn) => {
      btn.style.background = ""; // Reset background color
    });

    // Reset all answer texts
    document.querySelectorAll(".answer").forEach((answer) => {
      answer.textContent = "";
    });

    if (button === correctChoice) {
      button.style.background = "#16FF00"; // Change color to green
      document.querySelector("#correct-answer").textContent = "Correct!";
    } else {
      button.style.background = "red";
      const answerId = button.id.replace("btn", "answer");
      document.querySelector(`#${answerId}`).textContent = "Incorrect!";
    }
  });
});
// Initialize the check asnwer button
const checkButton = document.querySelector("#check-btn"); // Updated ID
const answerInput = document.querySelector("#free-response-input");
const textPopUp = document.querySelector("#inputOutput");

checkButton.addEventListener("click", function () {
  const answer = answerInput.value.trim().toLowerCase();

  if (answer === "switzerland") {
    textPopUp.textContent = "Correct!";
    textPopUp.style.color = "green";
    textPopUp.style.fontsize = "15px";
  } else {
    textPopUp.textContent = "Incorrect!";
    textPopUp.style.color = "red";
    textPopUp.style.fontsize = "15px";
  }
});