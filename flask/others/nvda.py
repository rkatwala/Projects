import yfinance as yf
import pandas as pd
import sqlite3  # Included in case you want to store data in a DB later

# 1. Define ticker and date range
ticker = 'NVDA'
start_date = '2024-01-01'
end_date = '2025-06-06'

# 2. Download NVDA stock data using yfinance
df = yf.download(ticker, start=start_date, end=end_date)

# 3. Print the full DataFrame to see what it looks like
print("📈 NVDA Stock Data:")
print(df)

# 4. Calculate and print the average closing price
avg = df["Close"].mean()
print("📊 Average Closing Price:")
print(avg.item())  # Ensures it's not a Series

