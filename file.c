#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>

int main(void) {
    CURL *curl;

    // Initialisation de libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    while (1) {  // Boucle infinie
        // Création de l'objet CURL
        curl = curl_easy_init();

        if (curl) {
            // Données JSON à envoyer
            const char *postData = "{\"temperature\": 25}";

            // URL de la requête POST
            curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9090/api/v1/zEKH1U9te4RBoOeFwwUU/telemetry");

            // Spécification du type de requête (POST)
            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            // Spécification du contenu JSON
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

            // En-tête Content-Type
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Exécution de la requête
            CURLcode res = curl_easy_perform(curl);

            // Vérification des erreurs
            if (res != CURLE_OK)
                fprintf(stderr, "Erreur curl : %s\n", curl_easy_strerror(res));

            // Libération des en-têtes
            curl_slist_free_all(headers);

            // Libération des ressources CURL
            curl_easy_cleanup(curl);
        }
        

        // Pause de 30 secondes avant la prochaine itération
        sleep(30);
    }

    // Libération des ressources globales de libcurl (ne sera jamais atteint dans ce cas)
    curl_global_cleanup();

    return 0;
}
