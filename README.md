# Raspberry V-Plan (QT)

Native QT application to display the MyTFG V-Plan on Raspberry Pis


## Setup development enivonment

### JsonCpp library

The project depends on the jsonCpp library to parse to MyTFG API responses.

You only need to generate amalgamated source and header files once:
```
cd raspVtp/jsonCpp
python amalgamate.py
```

