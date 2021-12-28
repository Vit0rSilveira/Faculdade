#Programa que calcula a média da discipliana ICC2
#Quaquer dúvida, falar com o baracus.
import os

def receber_notas(exercicios):
    print("\nCaso você tenha feito sub, use a nota da sub no lugar dela")
    print("Ou seja, substituindo a pior nota que você teve\n")
    p = []
    if exercicios == True:
        for i in range(5):
            temp = float(input(f"Digite a nota {i + 1} : " ))
            p.append(temp)
    else:
        for i in range(3):
            temp = float(input(f"Digite a nota {i + 1} : " ))
            p.append(temp)

    return sum(p) / len(p)

def calcular_media(provas, trabalhos, exercicios):
    p = 3 / (provas + 5)
    t = 2 /(trabalhos + 5)
    e = 1 / (exercicios + 5)

    media = 6 / (p + t + e)

    return media - 5

def main():
    nome = input("Qual seu nome: " )
    os.system('clear')

    print("Primeiro Vamos receber as notas das suas PROVAS")
    provas = receber_notas(False)
    os.system('clear')

    print("Depois Vamos receber as notas dos seus TRABALHOS")
    trabalhos = receber_notas(False)
    os.system('clear')

    print("Depois Vamos receber as notas dos seus EXERCÍCIOS")
    print("A avaliação por pares, você pode colocar onde quiser")
    exercicios = receber_notas(True)

    os.system('clear')
    print("A média que você obteve com as provas foi: ", provas)
    print("A média que você obteve com os trabalhos foi: ", trabalhos)
    print("A média que você obteve com os exercícios foi: ", exercicios)
    print()
    MF = calcular_media(provas, trabalhos, exercicios)
    print(nome + " sua media final em ICC2 é ", MF)



if __name__ == '__main__':
    main()