#include "RunPython.h"

bool PythonInstance::created = false;
PythonInstance* PythonInstance::instance = nullptr;

void PythonInstance::loadPackage(string packname)
{
	using std::cout;
//change path
#if 0
	string chdir_cmd = string("sys.path.append(\"") + localpath + "\")";
	const char* cstr_cmd = chdir_cmd.c_str();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString(cstr_cmd);
#endif
	// ����ģ��
	PyObject* moduleName = Py_BuildValue("s", packname.c_str()); //ģ�����������ļ���
	PyObject* pModule = PyImport_Import(moduleName);
	if (!pModule) // ����ģ��ʧ��
	{
		cout << "[ERROR] Python get module failed.\n";
		return;
	}
	packages[packname] = pModule;
	//cout << "[INFO] Python get module succeed.\n";
}

void PythonInstance::loadFunction(string packname, string funcname)
{
	using std::cout;
	auto pModule = packages[packname];
	// ���غ���
	PyObject* pv = PyObject_GetAttrString(pModule, funcname.c_str());
	if (!pv || !PyCallable_Check(pv))  // ��֤�Ƿ���سɹ�
	{
		cout << "[ERROR] Can't find function " <<funcname <<"\n";
		return;
	}
	//cout << "[INFO] Get function (test_add) succeed.\n";
}

PyObject *PythonInstance::getFunc(string funcname)
{
	return functions[funcname];
}

void testCall()
{
	// ���ò���
	PyObject* args = PyTuple_New(2);   // 2������
	PyObject* arg1 = Py_BuildValue("i", 4);    // ����һ��Ϊ4
	PyObject* arg2 = Py_BuildValue("i", 3);    // ��������Ϊ3
	PyTuple_SetItem(args, 0, arg1);
	PyTuple_SetItem(args, 1, arg2);

	// ���ú���
	PyObject* pRet = PyObject_CallObject(pv, args);

	// ��ȡ����
	if (pRet)  // ��֤�Ƿ���óɹ�
	{
		int result, r2 = 0;
		PyArg_ParseTuple(pRet, "(i)", &result);
		std::cout << "result:" << result << ' ' << r2;
	}
}
