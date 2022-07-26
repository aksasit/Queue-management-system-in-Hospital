#include <bits/stdc++.h>
using namespace std;

// This structure will store the details of patients required for registration.
struct patient_details
{
  char emergency;
  int department;
  string name;
  int age;
  string address;
  char gender;
  string blood_grp;
  int aadhar_no;
  int time;
};

// This data type will uniquely store the ID of each patient along with department for checkup.
struct patient_ID
{
  double ID;
  int dep;
};

// This data type will store the details of patients registered in particular department.
struct dep_queue
{
  int H[100];
  int size;
};

void swap(int &a, int &b)
{
  int temp;
  temp = a;
  a = b;
  b = temp;
}
// Below defined functions are for storing in max heap order
int parent(int i)
{
  return ((i - 1) / 2);
}

int leftChild(int i)
{
  return (2 * i + 1);
}

int rightChild(int i)
{
  return (2 * i + 2);
}

void shiftUp(int i, int *H)
{
  while (i > 0 && H[parent(i)] < H[i])
  {
    swap(H[parent(i)], H[i]);
    i = parent(i);
  }
}

void shiftDown(int i, int *H, int &size)
{
  int maxIndex = i;
  int l = leftChild(i);

  if (l <= size && H[l] > H[maxIndex])
  {
    maxIndex = l;
  }

  int r = rightChild(i);
  if (r <= size && H[r] > H[maxIndex])
  {
    maxIndex = r;
  }
  if (i != maxIndex)
  {
    swap(H[i], H[maxIndex]);
    shiftDown(maxIndex, H, size);
  }
}

void insert(int p, int *H, int &size)
{
  size = size + 1;
  H[size] = p;

  shiftUp(size, H);
}
int extractMax(int *H, int &size)
{
  int result = H[0];
  H[0] = H[size];
  size = size - 1;
  shiftDown(0, H, size);

  return result;
}

int main()
{

  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  // Number of patients who will be registering.
  int count_patient, i;
  cin >> count_patient;

  patient_details *patient_data = (patient_details *)malloc(count_patient * sizeof(patient_details));

  cout << "********************************************************************************************************\n\n";

  for (i = 0; i < count_patient; i++)
  {
    char ch;
    string str;
    int temp;

    cout << "Have you emergency case (Enter Y for Yes or N for NO)\n";
    cin >> ch;

    patient_data[i].emergency = ch;

    cout << "Do you know department or not:(Enter Y for Yes or N for NO)\n";
    cin >> ch;

    // If patient knows his/her department we will ask me his department number.
    // Otherwise he/she will be sent to physcian for diagnosis of the disease.

    if (ch == 'Y')
    {
      cout << "Enter department number \n\n";
      cout << " 0:Physician(OPD)\n 1:Gastroenterology (EMG)\n 2:Intensive Care Unit (ICU)\n 3:Neurology (NRO)\n 4:Oncology  (ONC) \n 5:ENT	(ENT) \n 6:Surgeon (SUG) \n 7:Cardiovascular (CVS)\n 8:Orthopaedic (ORP)\n 9:Pediatric (PDC)\n 10:Gynecologist(GYS) \n 11:Psychiatric(PST) \n 12:Dentistry(DNS) \n 13:Dermatology(DMT) \n 14:Radiology(RDY) \n 15:TraumaCentre (TMC)\n";

      cin >> temp;
      patient_data[i].department = temp;
    }
    else
    {
      cout << "\nWe will send you to OPD\n";
      patient_data[i].department = 0;
    }

    // Basic details have been asked for registration.

    cout << "\nEnter your Name\n";
    cin >> str;
    str = patient_data[i].name;

    cout << "Enter your age \n";
    cin >> temp;
    patient_data[i].age = temp;

    cout << "Enter your address\n";
    cin >> str;
    str = patient_data[i].address;

    cout << "Enter your Gender (Enter M for MALE , F for Female, O for others)\n";
    cin >> ch;
    patient_data[i].gender = ch;

    cout << "Do you know your blood group : (Enter Y for Yes or N for NO) \n";
    cin >> ch;

    if (ch == 'Y')
    {
      cout << "Enter Blood Group\n";
      cin >> str;
      str = patient_data[i].blood_grp;
    }
    else
    {
      str = "NA";
    }

    cout << "Enter your AADHAR NO.\n";
    cin >> temp;
    patient_data[i].aadhar_no = temp;

    cout << "Enter TIME \n\n";
    cin >> temp;
    patient_data[i].time = temp;

    cout << "********************************************************************************************************\n\n";
  }

  ////  UNIQUE ID GENERATION of each patient.
  //// Max heap concept is used here to decide priority.

  patient_ID *PAT_ID = (patient_ID *)malloc(count_patient * sizeof(patient_ID));

  for (i = 0; i < count_patient; i++)
  {
    if (patient_data[i].emergency == 'Y')
      PAT_ID[i].ID = 1;
    else
      PAT_ID[i].ID = 0;

    // To give less priority to late registrations time is being subtracted from 2400 (2400 is maximum time possible in 24 hour time format)

    patient_data[i].time = 2400 - patient_data[i].time;

    // i is added to patient ID because it will later help in extracting the required patient information.
    patient_data[i].time = patient_data[i].time * 1e4 + i;

    PAT_ID[i].ID = PAT_ID[i].ID * 1e8 + patient_data[i].time;
    PAT_ID[i].dep = patient_data[i].department;
  }

  dep_queue *DEP_Q = (dep_queue *)malloc(17 * sizeof(dep_queue));

  // Initialise size to -1 of each priority queue

  for (i = 0; i < 16; i++)
    DEP_Q[i].size = -1;

  for (i = 0; i < count_patient; i++)
  {
    int cur_dep = PAT_ID[i].dep;
    insert(PAT_ID[i].ID, DEP_Q[cur_dep].H, DEP_Q[cur_dep].size);
  }

  for (i = 0; i < 17; i++)
  {
    cout << "For the Department of ";
    switch (i)
    {
    case 0:
      cout << "Physician(OPD)\n";
      break;
    case 1:
      cout << "Gastroenterology\n";
      break;
    case 2:
      cout << "Intensive Care Unit (ICU)\n";
      break;
    case 3:
      cout << "Neurology (NRO)\n";
      break;
    case 4:
      cout << "Oncology (ONC)\n";
      break;
    case 5:
      cout << "ENT(ENT)\n";
      break;
    case 6:
      cout << "Surgeon (SUG)\n";
      break;
    case 7:
      cout << "Cardiovascular (CVS)\n";
      break;
    case 8:
      cout << "Orthopaedic (ORP)\n";
      break;
    case 9:
      cout << "Pediatric (PDC)\n";
      break;
    case 10:
      cout << "Gynecologist(GYS)\n";
      break;
    case 11:
      cout << "Psychiatric(PST)\n";
      break;
    case 12:
      cout << "Dentistry(DNS)\n";
      break;
    case 13:
      cout << "Dermatology(DMT)\n";
      break;
    case 14:
      cout << "Radiology(RDY)\n";
      break;
    case 15:
      cout << "TraumaCentre (TMC)\n";
      break;
    }

    if (DEP_Q[i].size == -1)
      cout << "No patient visited\n\n";
    else
    {
      cout << "The list of patients in sequential manner is as follows\n\n";

      while (DEP_Q[i].size >= 0)
      {

        int u = extractMax(DEP_Q[i].H, DEP_Q[i].size);
        int d = u - 10000 * (u / 10000);
        cout << "Patient name = " << patient_data[d].name << "\n";
        cout << "Patient ID = " << u << "\n\n";
      }
    }
    cout << "********************************************************************************************************\n\n";
  }
  return 0;
}
