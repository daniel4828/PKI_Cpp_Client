# Unser C++ Client
Dies ist unsere Client, um sich mit dem Gameserver zu verbinden, geschrieben in C++, da ja ursprünglich nur der Python Client zur Verfügung gestellt wurde. Wir hatten erst Probleme die Anbingung zu gestalten und haben auch mitbekommen, dass es anderen so geht, deswegen hoffen wir, dass hier kann helfen. 

Die Stellen, welche jeweils angepasst werden müssen, um den Anschluss an eure KI zu gewährleisten, haben wir hervorgehoben. Es geht hier größtenteils um den Konstruktor des Client. Hier müsst ihr für eure KI die passende Logik einbauen.

Wir entwickeln auf Unix und haben Boost.asio für das Managment vom Networktraffic genutzt. Wir haben deswegen noch angehangen, wie das Compilen auf Windows funktioniert, um eine Windows exe zu erhalten. 

Viel Erfolg!