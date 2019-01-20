#pragma once
#include <iostream>
#include <vector>
#include "dataType.h"
#include"obj.h"
#include <memory>
class SystemData
{
public:
	DataConfigListSet configData; //configList类型的集合
	DataConfig path;              //路径
	std::vector<std::vector<double>> _recoderData;
	std::vector<Obj *> _objData;
	SystemData() { std::cout << "sysData create successful" << std::endl; }
	~SystemData() = default;
	void addObj(Obj * obj)
	{
		_objData.push_back(obj);
	}
	void addRecoderData(std::vector<double> data)
	{
		_recoderData.push_back(data);
	}
	void showRecoderData()
	{
		for (auto &it1 : _recoderData)
		{
			for (auto &it2 : it1)
				std::cout << it2 << ";";
			std::cout << std::endl;
		}
	}
	void delAllMark(std::string &s, const std::string &mark)
	{
		size_t nSize = mark.size();
		while (1)
		{
			size_t pos = s.find(mark);    //  尤其是这里
			if (pos == std::string::npos)
			{
				return;
			}
			s.erase(pos, nSize);
		}
	}
	bool readSDcard(DataConfigList &data, const std::string &filePath)
	{
		FILE* file = fopen(filePath.c_str(), "r");
		if (file == nullptr)
		{
			std::cerr <<"路径 "<< filePath << " 打开错误" << std::endl;
			return false;
		}
		char buf[1024];
		std::string line;
		while (fgets(buf, 1024, file) != nullptr)//读取一行
		{
			line = buf;
			DataConfig tempData;
			delAllMark(line, " ");//删除多余的空格
			size_t del_idx = line.find("=");//记录等号的位置
			//解析密钥和值
			tempData.push_back(line.substr(0, del_idx));//添加KEY的值
			std::string val = line.substr(del_idx + 1, line.length());//添加VAL的值
			size_t val_idx = val.find(",");//搜索VAL的值记住找点 "," 的位置
			if (val_idx != std::string::npos)//如果搜到了逗号
				while (1)
				{
					tempData.push_back(val.substr(0, val_idx));//添加从0到逗号的区域
					val.erase(0, val_idx + 1);//删除逗号和逗号前的值
					val_idx = val.find(",");//迭代 继续找,号 m
					if (val_idx == std::string::npos)//如果最后没找到逗号了
					{
						tempData.push_back(val);//剩下的所有值全加进去
						break;
					}
				}
			else//没找到逗号就一个值咯
				tempData.push_back(val);
			//插入容器
			data.push_back({ tempData });
		}
		fclose(file);
		return true;
	}
	void rebuildSDcard(const DataConfigList &tempData, const std::string &name)
	{
		if (name == "底盘")
			path.push_back("chassis.txt");
		else if (name == "云台")
			path.push_back("head.txt");
		else if (name == "吸吐")
			path.push_back("intake.txt");
		else if (name == "旋转器")
			path.push_back("rotateIntake.txt");
		else if (name == "夹子")
			path.push_back("capIntake.txt");
		else if (name == "升降")
			path.push_back("lift.txt");
		else if (name == "弹射")
			path.push_back("shoot.txt");
		else
			std::cerr<< "读取部件名字错误,请检查程序"<<std::endl;
		configData.push_back(tempData);
		bool flag =readSDcard(configData.back(),path.back());
		if (!flag)
		{
			std::cerr << name << "没有搜索到" << name << "的文件.重新创建!请注意重新配置相关信息" << std::endl;
			bool flag = saveData(tempData, path.back());
			if (!flag)
				std::cerr << "二次保存失败!,请检查SD卡是否插入或者SD卡是否损坏!" << std::endl;
			else
				std::cout<<"路径 " << path.back() << " 创建成功" << std::endl;
		}
	}

	bool saveData(const DataConfigList &data, const std::string &filePath)
	{
		FILE *file = fopen(filePath.c_str(), "w");
		if (file == nullptr)
		{
			std::cerr << "路径 " << filePath << " 保存失败" << std::endl;
			return false;
		}
		for (auto &it : data)
		{
			std::string tempStr;//临时变量
			for (auto &it1 : it)
			{
				if (it1 == it.front())//如果是第一个元素 KEY
				{
					tempStr = it1;
					tempStr += "=";
				}
				else //VAL
				{
					tempStr += it1;
					if (it1 != it.back())//最后一个值后面不加逗号
						tempStr += ",";
				}
			}
			fprintf(file, "%s\n", tempStr.c_str());//逐行录入
		}
		fclose(file);
		return true;
	}
private:
};
extern SystemData* sysData;
