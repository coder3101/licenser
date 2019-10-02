# libLicenses.a
This submodules contains pre-existing popular license and its headers which can be used to directly initiate any license and its header without user provided setup. In order to add a new license type to this collections do following.

- Inherit a class named `LicenseShortName_` from `licenser::licenses::License`
- Override following 3 methods.
    - `body_to_string()` : The content returned from this is placed in LICENSE.txt file
    - `header_to_string()` : The content returned from this is placed in header of source
    - `name()` : The complete name of the header.
- Register the name License in the `LicenseTypes.hpp` in enum called `LicenseType`
- Register the name in `src/Licenses.cc` for name/enum switch block.

## Working Variables
The string returned from `body_to_string()` and `header_to_string()` can contain some placeholder types which are pre-processed before dumping into the License.txt and headers. These placeholdes are placed inside `%`.

Following is the complete list of placeholder

- `AUTHOR` : The name of the author of the software
- `YEAR_FROM` : The year of staring of project
- `YEAR_TO` : The year of ending of project
- `PROJECT` : The name of the Project
- `EMAIL` : Email of the Author

If your License needs to use these placeholders, please place these into `%` and preprocessor will handle it for you directly.

Example :
```cpp

class MyNewAwesomeLicense final : public License{
    ...
    std::string header_to_string() const override {
        return "Copyright (C) %PROJECT% was created by %%AUTHOR% from %YEAR_FROM% to %YEAR_TO%. For help send mail to %EMAIL%";
    }
};
```

The preprocessor will replace those placeholders with the respective values. 

> Note that the replaced values may not be singular incase of multiple author the placeholder %AUTHOR% refers to all the author and their names are separated by `,`. Same is true for %EMAIL%.
