import os
from bs4 import BeautifulSoup


def make_command(page):
    html_doc = open(page, "r", encoding="utf8")
    soup = BeautifulSoup(html_doc, "html.parser")

    title = soup.find("h1").text
    tds = soup.find_all("td")

    exs = []
    names = []
    for i, td in enumerate(tds):
        if td.text == "Submit directory":
            exs.append(tds[i + 1].text)
        if td.text == "Submit file":
            names.append(tds[i + 1].text)

    # for i, ex in enumerate(exs):
    #     os.mkdir(ex)
    #     with open(f"{ex}/{names[i]}", "w") as f:
    #         continue

    command = ""
    for i, ex in enumerate(exs):
        if i != 0:
            command += " && "
        command += f"mkdir {ex} && "
        command += f"touch {ex}/{names[i]}"

    with open("commands.txt", "a") as f:
        f.write(f"{title}\n{command}\n\n\n")


pages = os.listdir("pages")

for page in pages:
    if page.endswith(".html"):
        make_command(f"pages/{page}")
