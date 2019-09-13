# Computação Gráfica
Repositório para manter os programas da disciplina de Computação Gráfica de todo o grupo, separado em pastas com os nomes para entregas individuais e uma pasta para o grupo.

Cada pasta contém ~~*ainda não*~~ um script bash `upload.sh` e um `download.sh` que podem ser executados através do comando `bash upload.sh` ou `bash download.sh` que automatizam o procedimento de commit+push e merge+pull.

---

#### Comandos úteis do git
| Comando | Efeito | 
|---------|--------|
| `git config --global user.name "[seu_username]"` | Automatiza o uso do seu username nos commits. |
| `git clone [link_do_repositório]` | Clona um repositório do github na pasta atual. |
| `git add [caminho_relativo_do_arquivo]` | Adiciona um arquivo ao repositório. |
| `git commit -m "[mensagem_do_commit]"` | Salva as alterações feitas no repositório (arquivos incluídos, alterados, etc.) e insere a mensagem do commit. |
| `git push` | Envia as alterações salvas (pós-commit) para o diretório remoto; ou seja, upa no git. |
| `git status` | Exibe os arquivos alterados que ainda não foram salvos (não passaram por commit). |
| `git pull` | Faz o download dos arquivos do diretório e faz o 'merge' caso necessário. |
| `git merge` | Faz uma "fusão" do estado atual do diretório remoto (o que está no git) e o diretório local (o que sofreu commit, mas não passou pelo pull). Necessário quando mais de uma pessoa alteram o mesmo arquivo. |
| `git diff` | Exibe as diferenças dos arquivos ao passarem por merge e permite que o usuário escolha o que manter. |
