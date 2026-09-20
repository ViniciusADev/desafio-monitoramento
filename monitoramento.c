#include <stdio.h>

float lerEntrada_float(const char* mensagem) {
	float valor;
	char c;

	while (1) {
		printf("%s", mensagem);

		if (scanf("%f%c", &valor, &c) == 2 && (c == '\n' || c == ' ')) {
			return valor;
		}

		printf("Error: Entrada invalida! Por favor, digite um numero real valido.\n");

		int caracter;
		while ((caracter = getchar()) != '\n' && caracter != EOF);
	}
}

int main() {
	float limite_temperatura;
	float temp_atual;

	int total_leituras = 0;
	int total_acima_limite = 0;
	int tentativas_consecutivas = 0;

	float soma_temperaturas = 0.0;
	float maior_temp = 0.0;
	float menor_temp = 0.0;

	printf(" =====================================================\n"
	       "  SISTEMA DE MONITORAMENTO DE TEMPERATURA INDUSTRIAL\n"
	       " =====================================================\n");

	do {
		limite_temperatura = lerEntrada_float("Informe o limite de temperatura de seguranca (-50 a 150 C): ");

		if (limite_temperatura < -50.0 || limite_temperatura > 150.0) {
			printf("Error: O limite de seguranca deve estar entre -50 C e 150 C.\n");
		}
	} while (limite_temperatura < -50.0 || limite_temperatura > 150.0);

	printf("\nLimite seguro configurado para: %.2f C\n", limite_temperatura);
	printf("Iniciando... (Encerrara com 3 alertas consecutivos ou ao digita -999)\n");
	printf("-----------------------------------------------------\n");

	while (tentativas_consecutivas < 3) {
		temp_atual = lerEntrada_float("Digite a temperatura atual (Digite -999 para sair): ");

		if (temp_atual == -999.0) {
			break;
		}

		if (temp_atual < -100.0 || temp_atual > 200.0) {
			printf("Error: Temperatura fora da faixa do sensor (-100 C a 200 C).\n");
			continue;
		}

		total_leituras++;
		soma_temperaturas += temp_atual;

		if (total_leituras == 1) {
			maior_temp = temp_atual;
			menor_temp = temp_atual;
		} else {
			if (temp_atual > maior_temp) {
				maior_temp = temp_atual;
			}
			if (temp_atual < menor_temp) {
				menor_temp = temp_atual;
			}
		}

		if (temp_atual > limite_temperatura) {
			total_acima_limite++;
			tentativas_consecutivas++;
			printf("[ATENÇÃO] Temperatura ACIMA do limite, cuidado! (Consecutivas: %d/3)\n", tentativas_consecutivas);
		} else {
			if (tentativas_consecutivas > 0) {
				printf("[AVISO] Temperatura normalizada. Contador zerado.\n");
			}
			tentativas_consecutivas = 0;
			printf("[INFORME] Temperatura dentro do limite seguro.\n");
		}
	}

	if (total_leituras > 0) {
	    
		if (tentativas_consecutivas == 3) {
			printf("\n ================================================================\n"
			       "    ALERTA CRÍTICO: 3 TEMPERATURAS CONSECUTIVAS PASSOU DO LIMITE\n"
			       "    MONITORAMENTO INTERROMPIDO!!!\n"
			       " ================================================================\n\n");
		} else {
			printf("\n[INFORME] Operação encerrada pelo usuário.\n\n");
		}

		float media_temp = soma_temperaturas / total_leituras;
		float percentual_acima = ((float)total_acima_limite / total_leituras) * 100.0;

		printf("------ RELATÓRIO FINAL DE MONITORAMENTO -------\n");
		printf("Total de leituras validas realizadas : %d\n", total_leituras);
		printf("Maior temperatura registrada         : %.2f C\n", maior_temp);
		printf("Menor temperatura registrada         : %.2f C\n", menor_temp);
		printf("Média das temperaturas               : %.2f C\n", media_temp);
		printf("Total de leituras acima do limite    : %d\n", total_acima_limite);
		printf("Percentual de leituras com alerta    : %.2f%%\n", percentual_acima);
		printf("-----------------------------------------------\n");
	} else {
		printf("\nNenhuma leitura valida foi registrada no sistema.\n");
		printf("\nSaindo... Tchau!\n");
	}

	return 0;
}
