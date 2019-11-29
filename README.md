#ProjetoLockSmith
Projeto de uma trava inteligente onde a identificação de cartões via QRCode e o gerenciamento de acessos, são realizados em aplicativo Android.

#INSTALANDO O APLICATIVO
Faça o download do arquivo .apk. Passe-o para seu celular ou emulador android. Abra o arquivo em seu celular ou emulador. Aceite instalar e pronto!.

#ARQUIVO .aia
Este arquivo pode ser aberto no MIT AppInventor 2. Nele está contido o desing e código fonte do aplicativo. O arquivo está livre para ser usado para aprendizado.

#Esquema de Hardware
No arquivo "hardware_scheme.png" está o modelo lógico do esquema de hardware. Para monta-lo é nescessário: - 1 Fonte 12v 1A(mínimo); - 1 Fonte 5v xA; - 1 NodeMCU-esp8266; - 1 Relé 5V simples; - 1 Shield MFRC522; - 1 Traca Solenóide. - (Opcional) 1 Led. - (Opcional) 1 Resistor 220 ou 470 Ohms.

#Código do Hardware (.ino)
Baixe o código, abra-o na IDE arduino (https://www.arduino.cc/en/Main/Software) Configure a IDE para reconhecer o nodeMCU (https://blogmasterwalkershop.com.br/embarcados/nodemcu/nodemcu-configurando-a-ide-do-arduino/) Carregue o código para o NodeMCU Quando ele iniciar, abra o monitor serial para realizar a configuração inicial. Digite e mande os seguintes textos nessa ordem na entrada serial: - A sala que deseja que a tranca seja (exemplo: Room1); - O nome do wi-fi que deseja conectar o esp8266; - A senha do wi-fi que deseja conectar o esp8266. Pronto! Agora é só passar o cartão e usar o app para configurar o acesso!
