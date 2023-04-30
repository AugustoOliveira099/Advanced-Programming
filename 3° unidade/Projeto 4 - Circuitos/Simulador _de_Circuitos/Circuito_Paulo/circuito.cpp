#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include "circuito.h"
#include "bool3S.h"

//
// CLASS PORT
//

Port::Port(unsigned NI): saida(bool3S::UNDEF)
{
    if(NI!=0 && NI<5)
    {
        Nin = NI;
        for (unsigned i=0; i<4; i++)
        {
            id_in[i] = 0; //id_in indefinido
        }
    }
}

Port::Port(const Port &P)
{
    Nin = P.Nin;
    for (unsigned i=0; i<Nin; i++)
    {
        id_in[i] = P.id_in[i];
    }
    saida = P.saida;
}

int Port::getId_in(unsigned i) const
{
    i--;
    if(i>=0 && i<Nin)
    {
        return id_in[i];
    }
    return 0;
}

void Port::setNumInputs(unsigned N)
{
    if((1<N && N<5) && N!=Nin)
    {
        Nin = N;
    }
}

void Port::setOutput(bool3S s)
{
    if(getOutput()!=s)
    {
        saida = s;
    }
}

void Port::setId_in(unsigned i, int Id)
{
    i--;
    if((i>=0 && i<Nin))
    {
        if(getId_in(i+1)!=Id) id_in[i] = Id;
    }
}

void Port::digitar()
{
    unsigned prov_Nin;
    int prov;
    bool OK = true;

    //Leh o numero de entradas da porta
    cout << "Obs.: a porta possui de 2 a 4 entradas.\n"; // Informa a condicao
    do{
        cout << "Numero de entradas da porta:\n";
        cin >> prov_Nin;
    } while(prov_Nin<2 || prov_Nin>4);

    setNumInputs(prov_Nin);

    //Leh as ids das Nin entradas
    cout << "Digite as " << Nin << " ids:\n";

    for(unsigned i=1; i<=Nin; i++)
    {
        cin >> prov;
        if(prov==0) OK = false;
        if(OK) setId_in(i,prov);
    }
}

bool Port::ler(istream &I)
{
    // O cursor estah posicionado exatamente antes do numero que sucede o tipo da porta logica
    I >> Nin;
    if(Nin<2 || Nin>4) return false;
    I.ignore(); // Ignora o ":"
    for(unsigned i=0; i<Nin; i++)
    {
        I >> id_in[i]; // Leh as ids
        if(id_in[i]==0) return false; // Zero nao eh uma id valida
    }
    I.ignore(); // Ignora o \n

    return true;
}

ostream &Port::imprimir(ostream &O) const
{
    // Imprime a partir do numero de identificacao da id
    O << ") " << this->getName() << ' ' << Nin << ": ";
    for(unsigned i=0; i<Nin; i++)
    {
        O << id_in[i];
        if(i==(Nin-1))
            O << endl;
        else
            O << ' ';
    }
    return O;
}

//
// CLASS PORT_NOT
//

void Port_NOT::setNumInputs(unsigned N)
{
    if(N!=1){
        cerr << "A quantidade de entradas da porta logica NOT nao pode ser alterada, "
             << "ela possui apenas uma entrada.\n";
    }
}

void Port_NOT::digitar()
{
    int prov=0;
    bool OK = true;

    // Informa a condicao da porta
    cout << "Obs.: a porta NOT possui apenas uma entrada.\n";

    // Leh a id desejada
    cout << "Digite a id para a porta NOT em questao:\n";

    cin >> prov;
    if(prov==0) OK = false;

    if(OK) setId_in(1,prov);
}

bool Port_NOT::ler(istream &I)
{
    // O cursor estah posicionado exatamente antes do numero que sucede o tipo da porta logica
    I >> Nin;
    if(Nin!=1) return false; // Soh possui uma entrada
    I.ignore(); // Ignora o ":"
    I >> id_in[0]; // Leh a unica id
    if(id_in[0]==0) return false; // Zero nao eh uma id valida
    I.ignore(); // Ignora o enter

    return true;
}

//
// SIMULAR DE CADA CLASSE
//

bool3S Port_NOT::simular(const bool3S in[])
{
    return ~in[0];
}

bool3S Port_AND::simular(const bool3S in[])
{
    bool3S prov_saida = in[0] & in[1];

    for(unsigned i=0; i<(Nin-2); i++)
    {
        if(prov_saida==bool3S::FALSE) return bool3S::FALSE;
        prov_saida = prov_saida & in[i+2];
    }

    return prov_saida;
}

bool3S Port_NAND::simular(const bool3S in[])
{
    bool3S prov_saida = in[0] & in[1];

    for(unsigned i=0; i<(Nin-2); i++)
    {
        if(prov_saida==bool3S::FALSE) return bool3S::TRUE;
        prov_saida = prov_saida & in[i+2];
    }

    return ~prov_saida;
}

bool3S Port_OR::simular(const bool3S in[])
{
    bool3S prov_saida = in[0] | in[1];

    for(unsigned i=0; i<(Nin-2); i++)
    {
        if(prov_saida==bool3S::TRUE) return bool3S::TRUE;
        prov_saida = prov_saida | in[i+2];
    }

    return prov_saida;
}

bool3S Port_NOR::simular(const bool3S in[])
{
    bool3S prov_saida = in[0] | in[1];

    for(unsigned i=0; i<(Nin-2); i++)
    {
        if(prov_saida==bool3S::TRUE) return bool3S::FALSE;
        prov_saida = prov_saida | in[i+2];
    }

    return ~prov_saida;
}

bool3S Port_XOR::simular(const bool3S in[])
{
    bool3S prov_saida = in[0] ^ in[1];

    for(unsigned i=0; i<(Nin-2); i++)
    {
        if(prov_saida==bool3S::TRUE) return bool3S::TRUE;
        prov_saida = prov_saida ^ in[i+2];
    }

    return prov_saida;
}

bool3S Port_NXOR::simular(const bool3S in[])
{
    bool3S prov_saida = in[0] ^ in[1];

    for(unsigned i=0; i<(Nin-2); i++)
    {
        if(prov_saida==bool3S::TRUE) return bool3S::TRUE;
        prov_saida = prov_saida ^ in[i+2];
    }

    return ~prov_saida;
}

//
// CLASS CIRCUIT
//

void Circuit::alloc(unsigned NI, unsigned NO, unsigned NP)
{
    for(unsigned i=0; i<NI; i++)
    {
        inputs.push_back(bool3S::UNDEF);
    }

    for(unsigned i=0; i<NO; i++)
    {
        id_out.push_back(0);
    }

    for(unsigned i=0; i<NP; i++)
    {
        Port_AND arr;
        ports.push_back((&arr)->clone());
    }

}

void Circuit::copy(const Circuit &C)
{
    for(unsigned i=0; i<C.inputs.size(); i++) inputs.push_back(C.inputs[i]);

    for(unsigned i=0; i<C.id_out.size(); i++) id_out.push_back(C.id_out[i]);

    for(unsigned i=0; i<C.ports.size(); i++) ports.push_back(C.ports[i]->clone());
}

void Circuit::clean()
{
    inputs.clear();

    id_out.clear();

    for(unsigned i=0; i<ports.size(); i++) if(ports[i]!=nullptr) delete ports[i];
    ports.clear();
}

bool Circuit::valid() const
{
    if(getNumInputs()==0) return false;
    if(getNumOutputs()==0) return false;
    for(unsigned i=0; i<ports.size(); i++)
    {
        if((*ports[i]).getNumInputs()==0 || (*ports[i]).getNumInputs()>4) return false;

        for(unsigned j=1; j<=getNumInputsPort(i); j++)
        {
            // Verifica se alguma das ids que vai para a porta nao eh maior do que a quantidade
            // de portas existentes. Além disso, se a id nao eh menor do queh a quantidade
            // de entradas, uma vez que as entradas sao negativas, e se a id for menor,
            // significa que excedeu o numero de entradas. Ademais, se a id em questao eh 0, nao
            // eh valida.
            if( (getId_inPort(j,i) > int(getNumPorts())) ||
               (getId_inPort(j,i) < -int(getNumInputs())) ||
               (getId_inPort(j,i) == 0) )
                return false;
        }
    }

    for(unsigned i=0; i<getNumOutputs(); i++) if(id_out[i]==0) return false;

    return true;
}

bool3S Circuit::getInput(int IdIn) const
{
    if( (IdIn!=0) && (IdIn>= -int(getNumInputs())) )
    {
        return inputs[-IdIn-1];
    }

    return bool3S::UNDEF;
}

bool3S Circuit::getOutput(unsigned IdOut) const
{
    if(IdOut!=0 && IdOut<=getNumOutputs())
    {
        if(id_out[IdOut-1]<0) return getInput(id_out[IdOut-1]);
        else return (*ports[(id_out[IdOut-1]) - 1]).getOutput();
    }

    return bool3S::UNDEF;
}

int Circuit::getIdOutput(unsigned IdOut) const
{
    if(IdOut!=0 && IdOut<=getNumOutputs())
    {
        return id_out[IdOut-1];
    }
    return 0;
}

string Circuit::getNamePort(unsigned IdPort) const
{
    if(IdPort!=0 && IdPort<=getNumPorts())
    {
        return ports[IdPort-1]->getName();
    }
    return "";
}

unsigned Circuit::getNumInputsPort(unsigned IdPort) const
{
    if(IdPort!=0 && IdPort<=getNumPorts())
    {
        return (*ports[IdPort-1]).getNumInputs();
    }
    return 0;
}

int Circuit::getId_inPort(unsigned IdPort, unsigned i) const
{
    if(IdPort!=0 && IdPort<=getNumPorts())
    {
        if(i!=0 && i<=getNumInputsPort(IdPort))
        {
            return (*ports[IdPort-1]).getId_in(i);
        }
    }
    return 0;
}

void Circuit::setIdOutput(unsigned IdOut, int Id)
{
    if( (Id<=int(getNumPorts())) && (Id>=(-int(getNumInputs()))) && (Id!=0))
        id_out[IdOut-1] = Id;
}

void Circuit::setPort(unsigned IdPort, const string &T, unsigned NIn)
{
    if((T!=getNamePort(IdPort)) && (IdPort<=getNumPorts()))
    {
        if(T=="NT")
        {
            Port_NOT arr;
            ports[IdPort-1] = (&arr)->clone();
            (*ports[IdPort-1]).setNumInputs(NIn);
        }
        else if(T=="AN")
        {
            Port_AND arr;
            ports[IdPort-1] = (&arr)->clone();
            (*ports[IdPort-1]).setNumInputs(NIn);
        }
        else if(T=="NA")
        {
            Port_NAND arr;
            ports[IdPort-1] = (&arr)->clone();
            (*ports[IdPort-1]).setNumInputs(NIn);
        }
        else if(T=="OR")
        {
            Port_OR arr;
            ports[IdPort-1] = (&arr)->clone();
            (*ports[IdPort-1]).setNumInputs(NIn);
        }
        else if(T=="NO")
        {
            Port_NOR arr;
            ports[IdPort-1] = (&arr)->clone();
            (*ports[IdPort-1]).setNumInputs(NIn);
        }
        else if(T=="XO")
        {
            Port_XOR arr;
            ports[IdPort-1] = (&arr)->clone();
            (*ports[IdPort-1]).setNumInputs(NIn);
        }
        else if(T=="NX")
        {
            Port_NXOR arr;
            ports[IdPort-1] = (&arr)->clone();
            (*ports[IdPort-1]).setNumInputs(NIn);
        }
    }
}

void Circuit::setId_inPort(unsigned IdPort, unsigned I, int Id) const
{
    if(IdPort<=getNumPorts() && IdPort!=0){
        if( (Id<=int(getNumPorts())) && (Id>=(-int(getNumInputs()))) && (Id!=0) )
        {
            (*ports[IdPort-1]).setId_in(I,Id);
        }
    }
}

void Circuit::digitar()
{
    unsigned portas, entradas, saidas;
    int out=0;
    bool OK;
    string tipo, prov_entrada;

    cout << "Digite o numero de entradas, saidas e portas desejadas.\n";

    do
    {
        cout << "Numero de entradas:\n";
        cin >> entradas;
        cout << "Numero de saidas:\n";
        cin >> saidas;
        cout << "Numero de portas:\n";
        cin >> portas;
        if(entradas==0) cerr << "Eh preciso ter pelo menos uma entrada, "
                             << "digite novamente.\n";
        if(saidas==0) cerr << "Eh preciso ter pelo menos uma saida, "
                           << "digite novamente.\n";
        if(portas==0 && (entradas>saidas)) cerr << "Como existe apenas entradas e saidas, eh preciso que a quantidade de saidas "
                                                << "seja pelo menos iguais ao numero de entradas.\n";

    } while( (entradas==0) || (saidas==0) || (portas==0 && (entradas>saidas)) );

    clean();
    alloc(entradas, saidas, portas);

    // Caso queira ser simulado o circuito com determinadas entradas, sem gerar a tabela verdade,
    // basta passar como parametro para a funcao simular, da classe circuito, o vector inputs extraido
    // da seguinte forma:
    /*cin.ignore();
    for(unsigned i=0; i<getNumInputs(); i++)
    {
        do{
            cout << "Digite a(s) entrada(s) desejada(s).\n"
                 << "'T' para true, 'F' para false e '?' para undef:\n";
            getline(cin, prov_entrada);
            if( (prov_entrada!="T") && (prov_entrada!="F") && (prov_entrada!="?") )
                cerr << "Opcao invalida. Digite novamente:\n";
        } while( (prov_entrada!="T") && (prov_entrada!="F") && (prov_entrada!="?") );

        if(prov_entrada=="T") inputs[i] = toBool3S('T');
        else if(prov_entrada=="F") inputs[i] = toBool3S('F');
        else if(prov_entrada=="?") inputs[i] = toBool3S('?');
    } */

    if (portas>0)
    cout << "Tipos de portas:\n"
         << "NT para NOT;\n"
         << "AN para AND;\n"
         << "NA para NAND;\n"
         << "OR para OR;\n"
         << "NO para NOR;\n"
         << "XO para XOR;\n"
         << "NX para NXOR;\n";

    for(unsigned i=1; i<=portas; i++)
    {
        do
        {
            cout << "Digite qual o tipo desejado da porta " << i << ":\n";
            cin >> tipo;
        } while( (tipo!="NT") && (tipo!="AN") && (tipo!="NA") && (tipo!="OR") && (tipo!="NO") && (tipo!="XO") && (tipo!="NX") );

        if(tipo=="NT")
        {
            Port_NOT arr;
            ports[i-1] = (&arr)->clone();
            do
            {
                OK = true;
                ports[i-1]->digitar();
                for(unsigned j=1; j<=getNumInputsPort(i);j++)
                {
                    if( (getId_inPort(i,j)>int(getNumPorts())) || (getId_inPort(i,j)<(-int(getNumInputs()))) || (getId_inPort(i,j)==0) )
                    {
                        OK = false;
                        cerr << "A id " << getId_inPort(i,j) << " nao eh valida.\n";
                    }
                    if(!OK) cerr << endl << "Digite todos os dados da porta novamente.\n" << endl;
                }
            } while(!OK);
            setPort(i, tipo, 1);
        }
        else if(tipo=="AN")
        {
            Port_AND arr;
            ports[i-1] = (&arr)->clone();
            do
            {
                OK = true;
                ports[i-1]->digitar();
                for(unsigned j=1; j<=getNumInputsPort(i);j++)
                {
                    if( (getId_inPort(i,j)>int(getNumPorts())) || (getId_inPort(i,j)<(-int(getNumInputs()))) || (getId_inPort(i,j)==0) )
                    {
                        OK = false;
                        cerr << "A id " << getId_inPort(i,j) << " nao eh valida.\n";
                    }
                    if(!OK) cerr << endl << "Digite todos os dados da porta novamente.\n" << endl;
                }
            } while(!OK);
            setPort(i, tipo, getNumInputsPort(i));
        }
        else if(tipo=="NA")
        {
            Port_NAND arr;
            ports[i-1] = (&arr)->clone();
            do
            {
                OK = true;
                ports[i-1]->digitar();
                for(unsigned j=1; j<=getNumInputsPort(i);j++)
                {
                    if( (getId_inPort(i,j)>int(getNumPorts())) || (getId_inPort(i,j)<(-int(getNumInputs()))) || (getId_inPort(i,j)==0) )
                    {
                        OK = false;
                        cerr << "A id " << getId_inPort(i,j) << " nao eh valida.\n";
                    }
                    if(!OK) cerr << endl << "Digite todos os dados da porta novamente.\n" << endl;
                }
            } while(!OK);
            setPort(i, tipo, getNumInputsPort(i));
        }
        else if(tipo=="OR")
        {
            Port_OR arr;
            ports[i-1] = (&arr)->clone();
            do
            {
                OK = true;
                ports[i-1]->digitar();
                for(unsigned j=1; j<=getNumInputsPort(i);j++)
                {
                    if( (getId_inPort(i,j)>int(getNumPorts())) || (getId_inPort(i,j)<(-int(getNumInputs()))) || (getId_inPort(i,j)==0) )
                    {
                        OK = false;
                        cerr << "A id " << getId_inPort(i,j) << " nao eh valida.\n";
                    }
                    if(!OK) cerr << endl << "Digite todos os dados da porta novamente.\n" << endl;
                }
            } while(!OK);
            setPort(i, tipo, getNumInputsPort(i));
        }
        else if(tipo=="NO")
        {
            Port_NOR arr;
            ports[i-1] = (&arr)->clone();
            do
            {
                OK = true;
                ports[i-1]->digitar();
                for(unsigned j=1; j<=getNumInputsPort(i);j++)
                {
                    if( (getId_inPort(i,j)>int(getNumPorts())) || (getId_inPort(i,j)<(-int(getNumInputs()))) || (getId_inPort(i,j)==0) )
                    {
                        OK = false;
                        cerr << "A id " << getId_inPort(i,j) << " nao eh valida.\n";
                    }
                    if(!OK) cerr << endl << "Digite todos os dados da porta novamente.\n" << endl;
                }
            } while(!OK);
            setPort(i, tipo, getNumInputsPort(i));
        }
        else if(tipo=="XO")
        {
            Port_XOR arr;
            ports[i-1] = (&arr)->clone();
            do
            {
                OK = true;
                ports[i-1]->digitar();
                for(unsigned j=1; j<=getNumInputsPort(i);j++)
                {
                    if( (getId_inPort(i,j)>int(getNumPorts())) || (getId_inPort(i,j)<(-int(getNumInputs()))) || (getId_inPort(i,j)==0) )
                    {
                        OK = false;
                        cerr << "A id " << getId_inPort(i,j) << " nao eh valida.\n";
                    }
                    if(!OK) cerr << endl << "Digite todos os dados da porta novamente.\n" << endl;
                }
            } while(!OK);
            setPort(i, tipo, getNumInputsPort(i));
        }
        else if(tipo=="NX")
        {
            Port_NXOR arr;
            ports[i-1] = (&arr)->clone();
            do
            {
                OK = true;
                ports[i-1]->digitar();
                for(unsigned j=1; j<=getNumInputsPort(i);j++)
                {
                    if( (getId_inPort(i,j)>int(getNumPorts())) || (getId_inPort(i,j)<(-int(getNumInputs()))) || (getId_inPort(i,j)==0) )
                    {
                        OK = false;
                        cerr << "A id " << getId_inPort(i,j) << " nao eh valida.\n";
                    }
                    if(!OK) cerr << endl << "Digite todos os dados da porta novamente.\n" << endl;
                }
            } while(!OK);
            setPort(i, tipo, getNumInputsPort(i));
        }
    }

    cout << "Agora digite a(s) id(s) para a(s) saida(s).\n";
    for(unsigned i=1; i<=getNumOutputs(); i++)
    {
        do
        {
            if(getNumOutputs()>1) cout << "Digite a id da saida " << i << ":\n";
            else cout << "Digite a unica id:\n";
            cin >> out;
            if( (out==0) || (out>int(getNumPorts())) || (out<(-int(getNumInputs()))) )
                cerr << "Digite uma id valida.\n";
        } while( (out==0) || (out>int(getNumPorts())) || (out<(-int(getNumInputs()))) );
        setIdOutput(i,out);
    }
}

bool Circuit::ler(const string &arq)
{
    ifstream I(arq.c_str());
    if(!I.is_open()) return false;

    string circ, port, tipo, saidas;
    char parenteses;
    unsigned NI, NO, NP, id_prov;
    int id;

    I >> circ;
    if(circ!="CIRCUITO:")
    {
        I.close();
        return false;
    }

    // Antes de ler o arquivo, limpa os dados atuais do circuitp
    clean();

    I >> NI >> NO >> NP; // Recebe "CIRCUITO:"
    I.ignore(); // Ignora o \n
    if((NI==0) || (NO==0) || ((NP==0) && (NI>NO)))
    {
        I.close();
        clean();
        return false;
    }

    clean();
    alloc(NI,NO,NP);

    I >> port; // Recebe "PORTAS:"
    I.ignore(); // Ignora o \n
    if(port!="PORTAS:")
    {
        I.close();
        clean();
        return false;
    }

    for(unsigned i=1; i<=NP; i++)
    {
        I >> id_prov; // Recebe a id correspondente a i
        if(id_prov!=i)
        {
            I.close();
            clean();
            return false;
        }

        parenteses = I.peek();
        if(parenteses!=')')
        {
            I.close();
            clean();
            return false;
        }
        I.ignore(numeric_limits<streamsize>::max(),')');

        I >> tipo;
        if(tipo=="NT")
        {
            Port_NOT arr;
            ports[i-1] = (&arr)->clone();
            if(!(*ports[i-1]).ler(I))
            {
                I.close();
                clean();
                return false;
            }
        }
        else if(tipo=="AN")
        {
            Port_AND arr;
            ports[i-1] = (&arr)->clone();
            if(!(*ports[i-1]).ler(I))
            {
                I.close();
                clean();
                return false;
            }
        }
        else if(tipo=="NA")
        {
            Port_NAND arr;
            ports[i-1] = (&arr)->clone();
            if(!(*ports[i-1]).ler(I))
            {
                I.close();
                clean();
                return false;
            }
        }
        else if(tipo=="OR")
        {
            Port_OR arr;
            ports[i-1] = (&arr)->clone();
            if(!(*ports[i-1]).ler(I))
            {
                I.close();
                clean();
                return false;
            }
        }
        else if(tipo=="NO")
        {
            Port_NOR arr;
            ports[i-1] = (&arr)->clone();
            if(!(*ports[i-1]).ler(I))
            {
                I.close();
                clean();
                return false;
            }
        }
        else if(tipo=="XO")
        {
            Port_XOR arr;
            ports[i-1] = (&arr)->clone();
            if(!(*ports[i-1]).ler(I))
            {
                I.close();
                clean();
                return false;
            }
        }
        else if(tipo=="NX")
        {
            Port_NXOR arr;
            ports[i-1] = (&arr)->clone();
            if(!(*ports[i-1]).ler(I))
            {
                I.close();
                clean();
                return false;
            }
        }

        // Testa se as ids lidas sao validas
        for(unsigned j=1; j<=getNumInputsPort(i);j++)
        {
            if( (getId_inPort(i,j)>int(getNumPorts())) || (getId_inPort(i,j)<(-int(getNumInputs()))) || (getId_inPort(i,j)==0) )
            {
                I.close();
                clean();
                return false;
            }
        }

    }

    // Stream posicionada exatamente antes de "SAIDA:"
    getline(I, saidas);
    if(saidas!="SAIDAS:")
    {
        I.close();
        clean();
        return false;
    }

    for(unsigned i=1; i<=getNumOutputs(); i++)
    {
        I >> id_prov; // Recebe a IdOut correspondente a i
        if(id_prov!=i)
        {
            I.close();
            clean();
            return false;
        }

        parenteses = I.peek();
        if(parenteses!=')')
        {
            I.close();
            clean();
            return false;
        }
        I.ignore(numeric_limits<streamsize>::max(),')');

        // Recebe a id da saida
        I >> id; // Recebe a id que a saida i retorna
        I.ignore(); // Ignora o \n
        if( (id>int(getNumPorts())) || (id<(-int(getNumInputs()))) || (id==0))
        {
            I.close();
            clean();
            return false;
        }

        setIdOutput(i,id);
    }

    I.close();
    if(valid()) return true;
    else return false;
}

ostream &Circuit::imprimir(ostream &O) const
{
    O << "CIRCUITO: " << getNumInputs() << ' ' << getNumOutputs() << ' ' << getNumPorts() << endl
                      << "PORTAS:\n";
    for(unsigned i=1; i<=getNumPorts(); i++)
    {
        O << i;
        (*ports[i-1]).imprimir(O);
    }

    O << "SAIDAS:\n";
    for(unsigned i=1; i<=getNumOutputs(); i++)
    {
        O << i << ") " << getIdOutput(i) << endl;
    }

    return O;
}

bool Circuit::salvar(const string &arq) const
{
    ofstream O(arq.c_str());
    if(!O.is_open()) return false;

    imprimir(O);

    O.close();
    return true;
}

bool Circuit::simular(const vector<bool3S> &Inputs)
{
    if(getNumInputs() != Inputs.size()) return false;

    inputs = Inputs;

    for(unsigned i=0; i<getNumPorts(); i++)
    {
        (*ports[i]).setOutput(bool3S::UNDEF);
    }

    bool tudo_def, alguma_def;
    int id=0;
    bool3S in[4];

    do
    {
        tudo_def = true;
        alguma_def = false;
        for(unsigned i=1; i<=getNumPorts(); i++)
        {
            if((*ports[i-1]).getOutput()==bool3S::UNDEF)
            {
                for(unsigned j=1; j<=getNumInputsPort(i); j++)
                {
                    id = getId_inPort(i,j);
                    if(id>0) in[j-1] = (*ports[id-1]).getOutput();
                    else in[j-1] = inputs[-id-1];
                }
                (*ports[i-1]).setOutput(ports[i-1]->simular(in));
                if((*ports[i-1]).getOutput() == bool3S::UNDEF) tudo_def = false;
                else alguma_def = true;
            }
        }

    } while(!tudo_def && alguma_def);

    return true;
}


