# refactored: 
# https://towardsdatascience.com/web-scraping-html-tables-with-python-c9baba21059

import requests
import lxml.html as lh
import pandas as pd

url = 'http://pokemondb.net/pokedex/all'

page = requests.get(url)                       # page handle
doc  = lh.fromstring(page.content)             # website contents
tr   = doc.xpath('//tr')                       # html <tr> data
col  = [(t.text_content(), []) for t in tr[0]] # column titles

# scrape data
for T in tr[1:]:
    for i, t in enumerate(T.iterchildren()):
        data = t.text_content() 
        col[i][1].append(int(data) if data.isnumeric() else data)

Dict = {title:column for (title,column) in col}
df   = pd.DataFrame(Dict)

print(df.head())
