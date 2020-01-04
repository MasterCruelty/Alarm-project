# progetto allarme per il corso di sistemi embedded

*Autore*: Roberto Antoniello

*Descrizione*: consiste nel simulare un rilevatore di movimento tramite l'uso di sensori di prossimità ad ultrasuoni. Dopo un iniziale monitoraggio dell'ambiente, viene definita per ogni sensore la situazione tipica in seguito ad un certo numero di misurazioni. Una volta che vengono definiti questi valori, i sensori effettueranno misurazioni periodicamente e nel caso in cui viene notato un cambiamento anormale scatterà l'allarme.
In caso di violazione un buzzer inizierà a suonare e verrà inviata una segnalazione via MQTT. Per disattivare l'allarme sarà richiesto un codice di sblocco e se corretto, il sistema riprenderà con le misurazioni periodiche.


*Licenza scelta*: GPLv3



