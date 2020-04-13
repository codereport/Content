# refactored: 
# https://towardsdatascience.com/web-scraping-html-tables-with-python-c9baba21059

import requests
import lxml.html as lh
import pandas as pd

url = 'http://pokemondb.net/pokedex/all'

page   = requests.get(url)                 # page handle
doc    = lh.fromstring(page.content)       # website contents
tr     = doc.xpath('//tr')                 # html <tr> data
titles = [t.text_content() for t in tr[0]] # column titles

fmt    = lambda data : int(data) if data.isnumeric() else data
cols   = zip(*[[fmt(t.text_content()) for t in T.iterchildren()] for T in tr[1:]])

Dict   = {title: column for title, column in zip(titles, cols)}
df     = pd.DataFrame(Dict)

print(df.head())
