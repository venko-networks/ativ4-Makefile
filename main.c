#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <openssl/md5.h> 

void* tarefa_thread(void* arg) {
    printf("[Thread %s] Iniciada.\n", (char*)arg);
    sleep(1);
    return NULL;
}

// v2: Nova thread para monitorar o tempo de atividade
void* monitor_uptime(void* arg) {
    FILE *fp = fopen("/proc/uptime", "r");
    if (fp) {
        double uptime;
        fscanf(fp, "%lf", &uptime);
        printf("[Monitor] O sistema está ligado há %.2f segundos.\n", uptime);
        fclose(fp);
    }
    return NULL;
}

int main() {
    // 1. Dependência de Execução (RDEPENDS)
    printf("v2.0 - Iniciando Verificações Elsys...\n");
    if (system("which curl > /dev/null 2>&1") != 0) {
        fprintf(stderr, "Erro: Dependência de execução (curl) não encontrada!\n");
        return 1;
    }

    // 2. Uso da OpenSSL (Dependência de Compilação - DEPENDS)
    unsigned char digest[MD5_DIGEST_LENGTH];
    const char* string = "Elsys_Challenge_V2";
    MD5((unsigned char*)string, 18, digest);

    printf("Hash MD5 v2: ");
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", digest[i]);
    printf("\n");

    pthread_t t1, t2;
    
    // Agora usando duas threads distintas
    pthread_create(&t1, NULL, tarefa_thread, "Worker");
    pthread_create(&t2, NULL, monitor_uptime, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("v2 finalizada com sucesso.\n");
    return 0;
}
