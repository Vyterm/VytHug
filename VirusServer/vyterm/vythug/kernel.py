from abc import abstractmethod
from enum import Enum
from vyterm.sqladapter import SqlAdapter
from vyterm.utils import singleton, get_instance
from vyterm.cryptography import md5str


class OpCommand(Enum):
    Kernel = 0
    Virus = 1


class KernelCommand(Enum):
    Version = 0


class VirusCommand(Enum):
    Check = 0
    Over = 1
    Submit = 2


@get_instance
@singleton
class Caches(object):
    def __init__(self):
        self.mysql = SqlAdapter(db="virus_db", password="1JXahbu230x1Zehim88t")
        self.viruses = {}
        for virus in self.mysql.select("select `virus_tag`, `virus_name` from `md5_virus_table`;"):
            tag, name = virus
            self.viruses[tag] = name

    def is_virus(self, virus_md5: str) -> bool:
        return virus_md5 in self.viruses

    def get_name(self, virus_md5: str) -> str:
        return self.viruses[virus_md5]

    def submit(self, virus_md5: str):
        self.mysql.execute("insert into `md5_virus_table`(`virus_tag`) values (%s);" % virus_md5)


class Handler(object):
    @property
    @abstractmethod
    def handlers(self):
        pass

    def execute(self, client, command, packet):
        if command in self.handlers:
            self.handlers[command](client, packet)
            return True
        else:
            return False

    @abstractmethod
    def logout(self, client):
        pass


if __name__ == '__main__':
    assert id(Caches()) == id(Caches())
    assert id(Caches.get()) == id(Caches.get())
    print("All tests of VytHug.kernel passed!")
    pass
