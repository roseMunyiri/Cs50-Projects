import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# Initialize an empty list to store user entries
user_entries = []


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":


        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthday_data = db.execute("SELECT id, name, month, day FROM birthdays")

        return render_template("index.html", birthday_data = birthday_data)

# Deregister a person from the list
@app.route("/deregister", methods=["POST"])
def deregister():
    deregister_id = request.form.get("id")
    print("deregister_id:", deregister_id)  # Debug print


    # Delete a user
    if deregister_id:
        db.execute("DELETE FROM birthdays WHERE id = ?", deregister_id)

    return redirect("/")

if __name__ == '__main__':
    app.run(debug=True)


