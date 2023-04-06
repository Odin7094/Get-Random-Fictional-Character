# getRandCharacter
Get a random fictional character based on wikidata's exported characters.

It is simple'n'all but if it was done I would've saved some bit of time so here it is for others. I might've been bad at searching tho.

Another thing is I think it's a good thing to do to put wikidata csv exports here so their servers have it a bit easier and people don't need to trial'n'error select their database for this use-case.

## DIY - Query
If you want to get data yourself here is what I did.

I dunno if it's all fine of a query, I think it's fine.
Put it at https://query.wikidata.org and download preferable data format.

This query results in charactersWithArticles.csv's content. It searches for characters with at least one wikipedia en article.
```
SELECT DISTINCT ?item ?itemLabel WHERE {
  ?article schema:about ?item ;
             schema:isPartOf <https://en.wikipedia.org/> .
  # Item's type is: fictional character, or sub-type, or sub-sub-type, etc.
  ?item p:P31/ps:P31/wdt:P279* wd:Q95074.
  OPTIONAL{?item wdt:P1441 ?work}
  SERVICE wikibase:label {
    bd:serviceParam wikibase:language "en". # You can specify more languages.
  }
```

I'm pretty sure that for just getting it all I've used the first query in [this stackexchange reply](https://opendata.stackexchange.com/a/18523) and have removed duplicates using notepad++. I've removed them locally not because it was the better option but because I've already had the csv on my disk. Throwing distinct at it would also probably do the trick.

## What is it? How do I use it?
C++ console app that uses CGI to output into browser. In practice I just change .exe to .cgi and put it behind xampp(cgi-bin, not htdocs) and print my data in html format. Here I just skipped everything but content-type and link tag, so it's probably incorrect if you care about having whole html structure in there but it prints anyway and I didn't care.(not that it's hard, just useless for the case)

Output is a random entry from csv in amount equal 1 or whatever you input in GET(like http://localhost/cgi-bin/randCharacter.cgi?20 for 20) in a form of a link to wikidata source and name of the character.

If you want to recompile then the build.bat script just runs g++ that outputs file with cgi extension into the right folder.
In one place in code there is one thing copied from [there](https://stackoverflow.com/a/600014) because I didn't remember how to quickly do that in cpp without parsing it myself.

It is possible xammp's apache will need some .ini parameters switched to allow cgi execution but I don't remember if and how I did do that years ago. Google will have solution.

## Quick guide to use
Place CSV in the same folder(.../xampp/cgi-bin for example) as the .cgi, boot up your server(for me xampp cuz quick and easy) and enter through url.

It doesn't check if the file exists or anything and is set straight up in the code to open charactersWithArticles.csv so for quick """install""" use this file.

![UseExample](https://media.discordapp.net/attachments/321695978531061761/1093638925131726938/image.png)

## Contributions
Feel free to contribute if you want to I guess. I don't really expect it tho. If not for getting those csvs I would probably not even have made the repository.
