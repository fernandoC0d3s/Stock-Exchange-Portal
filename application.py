import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    """Show history of transactions"""

    userid = session["user_id"] 
    totalValue=0
    user = db.execute("SELECT * FROM users WHERE id = :userid",userid=userid)
    cash =user[0]["cash"]
 
    username= user[0]["username"]
    stocks = db.execute("DELETE FROM portfolio2 WHERE userid= :userid AND quantity = 0", userid=username)
    stocks = db.execute("SELECT * FROM portfolio2 WHERE userid = :userid", userid=username)
    if len(stocks) ==0:
        return apology("You need to buy stonks")
    elif len(stocks) != 0:    
        for stock in stocks:
            symbol = stock["symbol"]
            shares = stock["quantity"]
            name = lookup(symbol)["name"]
            price = lookup(symbol)["price"]
            total = shares * price
            stock["name"] = name
            stock["price"] = usd(price)
            stock["total"] = usd(total)
            totalValue = totalValue + total
            portfolioValue = usd(totalValue+cash)
    return render_template("index.html",stocks=stocks,cash=usd(cash), totalValue=totalValue, portfolioValue = portfolioValue)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method =="GET":
       return render_template("buy.html")
    elif request.method=="POST":
        stock = request.form.get("stock")
        quantity= int(request.form.get("quantity"))
        
        
        result = lookup(stock)
        if result != None:
            price = result["price"]
            userid = session["user_id"] 
            symbol= result["symbol"]
        
            rows = db.execute("SELECT * FROM users WHERE id = :userid",
                          userid=userid)
            cash =rows[0]["cash"]            
            username =rows[0]["username"]
                  
            orderprice = quantity * price             
            if orderprice > cash:
                return apology("TODO123")
            
            elif orderprice <= cash:
                db.execute("INSERT INTO orders (userid, symbol, quantity, price) VALUES (:username, :symbol, :quantity, :price)", username=username, symbol=symbol,quantity=quantity,price=price)
                verification = db.execute("SELECT * FROM portfolio2 WHERE symbol = :symbol AND userid=:userid", symbol=symbol, userid=username)
                if len(verification) == 0:
                    db.execute("INSERT INTO portfolio2 (userid, symbol, quantity) VALUES (:username, :symbol, :quantity)", username=username, symbol=symbol,quantity=quantity)
                    
                elif len(verification) == 1:
                    rowsOne = db.execute("SELECT * FROM portfolio2 WHERE symbol= :symbol AND userid = :userid",symbol=symbol, userid=username)
                    oldquant = rowsOne[0]["quantity"]
                    quantity = quantity + oldquant
                    db.execute("UPDATE portfolio2 SET quantity= :quantity WHERE symbol= :symbol AND userid = :userid", quantity=quantity, symbol=symbol, userid=username)
                    
                cash = cash - orderprice
                db.execute("UPDATE users SET cash= :cash WHERE id= :userid", userid=userid, cash=cash)
                return redirect("/")
        else:
            return apology("Check SYMBOL")
            
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    userid = session["user_id"] 
        
    rows = db.execute("SELECT * FROM users WHERE id = :userid",userid=userid)
    cash =rows[0]["cash"]            
    username =rows[0]["username"]
    rowsTwo = db.execute("SELECT * FROM orders WHERE userid = :userid", userid=username)
    
    return render_template("history.html", rowsTwo=rowsTwo)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method =="GET":
        return render_template("quote.html")
    elif request.method=="POST":
        stock = request.form.get("stock")
        result = lookup(stock)
        if result == None:
            return apology("NOT FOUND")
        elif result != None:
            return render_template("quoted.html",result=result)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        secondPassword = request.form.get("secondPassword")
        
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if secondPassword != password:
             return apology("invalid username and/or password", 403)
        if len(rows) == 1 or len(username) == 0:
            return apology("invalid username and/or password", 403)
        password = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=username, password=password)
        return redirect("/")
    


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method =="GET":
       return render_template("sell.html")
    elif request.method=="POST":
        stock = request.form.get("stock")
        quantity= int(request.form.get("quantity"))
        
        
        result = lookup(stock)
        if result != None:
            price = result["price"]
            userid = session["user_id"] 
            symbol= result["symbol"]
        
            rows = db.execute("SELECT * FROM users WHERE id = :userid",
                          userid=userid)
            cash =rows[0]["cash"]            
            username =rows[0]["username"]
           
            
            verification = db.execute("SELECT * FROM portfolio2 WHERE symbol = :symbol AND userid=:userid", symbol=symbol, userid=username)
            if len(verification) == 0:
                return apology("You do not own the stock")
            elif len(verification) !=0:
                 rows = db.execute("SELECT * FROM portfolio2 WHERE symbol= :symbol AND userid = :userid", symbol=symbol, userid=username)
                 quantityOwned = rows[0]["quantity"]
                 if quantityOwned >= quantity:
                     placed = quantity * -1
                     db.execute("INSERT INTO orders (userid, symbol, quantity, price) VALUES (:username, :symbol, :quantity, :price)", username=username, symbol=symbol,quantity=placed,price=price)
                     orderValue = quantity * price 
                     #need to query old value 
                     quantityOwned = quantityOwned-quantity;
                     db.execute("UPDATE portfolio2 SET quantity= :quantity WHERE symbol= :symbol AND userid = :userid", quantity=quantityOwned, symbol=symbol, userid=username)
                     cash = cash + orderValue
                     db.execute("UPDATE users SET cash= :cash WHERE id= :userid", userid=userid, cash=cash)
                     return redirect("/")
                 elif quantity < quantityOwned:
                    return apology("do not own many stocks")
                     
                
    
@app.route("/profile", methods=["GET", "POST"])
@login_required
def profile():
    userid = session["user_id"] 
    if request.method =="GET":
        rows = db.execute("SELECT * FROM users WHERE id = :userid",userid=userid)
        cash =rows[0]["cash"]            
        username =rows[0]["username"]
        return render_template("profile.html",username = username, cash=usd(cash))
    elif request.method =="POST":
        rows = db.execute("SELECT * FROM users WHERE id = :userid",userid=userid)
        cash =rows[0]["cash"]    
        newCash = request.form.get("cash")
        if newCash.isnumeric() == True:
            newCash = int(request.form.get("cash"))
            final = cash + newCash
            db.execute("UPDATE users SET cash = :cash WHERE id= :userid", userid=userid, cash = final)
            return redirect("/")
        elif newCash.isnumeric() == False:
            return apology("SNEAKY")
        

    


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
