import Joi from "joi";
import toast from "react-hot-toast";

export function useValidateUsername(username) {
	const schema = Joi.object({
		username: Joi.string().alphanum().min(3).max(30).required(),
	});

	const toVal = { username };

	try {
		return schema.validate(toVal);
	} catch (err) {
		toast.error(err);
	}
}
